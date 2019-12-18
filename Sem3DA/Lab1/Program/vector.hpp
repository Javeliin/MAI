#include <algorithm>
#include <cassert>
#include <stdexcept>


namespace NVector {

template <typename T>
class TVector {
public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    TVector():
        alreadyUsed(0), storageSize(0), storage(nullptr)
    {
    }

    TVector(int size, const value_type& defaultValue = value_type()):
        TVector()
    {
        assert(size >= 0);

        if (size == 0) {
            return;
        }

        alreadyUsed = size;
        storageSize = size;
        storage = new value_type[size];

        std::fill(storage, storage + alreadyUsed, defaultValue);
    }

    int Size() const {
        return alreadyUsed;
    }

    bool Empty() const {
        return Size() == 0;
    }

    iterator Begin() const {
        return storage;
    }

    iterator End() const {
        if (storage) {
            return storage + alreadyUsed;
        }
        return nullptr;
    }

    friend void Swap(TVector& lhs, TVector& rhs) {
        using std::swap;

        swap(lhs.alreadyUsed, rhs.alreadyUsed);
        swap(lhs.storageSize, rhs.storageSize);
        swap(lhs.storage, rhs.storage);
    }

    TVector& operator=(TVector other) {
        Swap(*this, other);
        return *this;
    }

    TVector(const TVector& other):
        TVector()
    {
        TVector next(other.storageSize);
        next.alreadyUsed = other.alreadyUsed;

        if (other.storage) {
            std::copy(other.storage, other.storage + other.storageSize,
                    next.storage);
        }

        Swap(*this, next);
    }

    ~TVector() {
        delete[] storage;

        storageSize = 0;
        alreadyUsed = 0;
        storage = nullptr;
    }

    void PushBack(const value_type& value) {
        if (alreadyUsed < storageSize) {
            storage[alreadyUsed] = value;
            ++alreadyUsed;
            return;
        }

        int nextSize = 1;
        if (storageSize) {
            nextSize = storageSize * 2;
        }

        TVector next(nextSize);
        next.alreadyUsed = alreadyUsed;

        if (storage) {
            std::copy(storage, storage + storageSize, next.storage);
        }

        next.PushBack(value);
        Swap(*this, next);
    }

    const value_type& At(int index) const {
        if (index < 0 || index > alreadyUsed) {
            throw std::out_of_range("Out of range");
        }
        return storage[index];
    }

    value_type& At(int index) {
        const value_type& elem = const_cast<const TVector*>(this)->At(index);
        return const_cast<value_type&>(elem);
    }

    const value_type& operator[](int index) const {
        return At(index);
    }

    value_type& operator[](int index) {
        return At(index);
    }

private:
    int alreadyUsed;
    int storageSize;
    value_type* storage;
};

}
