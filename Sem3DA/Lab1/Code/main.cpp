#include <stdio.h>
#include <cassert>
#include <algorithm>


const int RANGE = 1000000;

template <typename T>

class TVector {
public:
    using valueType = T;
    using iterator = valueType*;

    TVector() {
        used = 0;
        size = 0;
        storage = nullptr;
    }

    TVector(int newSize, const valueType& defaultValue = valueType()) :
        TVector() 
    {
        assert(newSize >= 0);
        if (newSize == 0) {
            return;
        }

        used = newSize;
        size = newSize;
        storage = new valueType[newSize];

        std::fill(storage, storage + used, defaultValue);
    }

    friend void Swap(TVector& left, TVector& right) {
        using std::swap;

        swap(left.used, right.used);
        swap(left.size, right.size);
        swap(left.storage, right.storage);
    }

    TVector(const TVector& newVector):
        TVector()
    {
        TVector next(newVector.size);
        next.used = newVector.used;

        if (newVector.storage != nullptr) {
            std::copy(newVector.storage, newVector.storage + newVector.size,
                    next.storage);
        }

        Swap(*this, next);
    }

    int Size() const {
        return used;
    }

    bool IsEmpty() const {
        return Size() == 0;
    }

    iterator Begin() const {
        return storage;
    }

    iterator End() const {
        if (storage != nullptr) {
            return storage + used;
        } 
        return nullptr;
    }

    void Push(const valueType& value) {
        if (used < size) {
            storage[used] = value;
            ++used;
        } else {
            int nextSize = 1;

            if (size > 0) {
                nextSize = size * 2;
            }

            TVector next(nextSize);
            next.used = used;

            if (storage != nullptr) {
                std::copy(storage, storage + size, next.storage);
            }

            next.Push(value);
            Swap(*this, next);
        }
    }

    valueType& At(int index) {
        if (index < 0 || index > used) {
            return storage[used];
        }
        return storage[index];
    }

    valueType& operator[](int index) {
        return At(index);
    }

    TVector& operator=(TVector newVector) {
        Swap(*this, newVector);
        return *this;
    }

    ~TVector() {
        delete[] storage;

        size = 0;
        used = 0;
        storage = nullptr;
    }

private:
    int used;
    int size;
    valueType* storage;
};

struct Post {
    unsigned long long int data;
    int key;
};

void CountingSort(TVector<Post>& source) {
    int sourceSize = source.Size();
    TVector<int> count(RANGE, 0);
    TVector<Post> result(sourceSize);

    for (int i = 0; i < sourceSize; ++i) {
        ++count[source[i].key];
    }

    for (int i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = sourceSize - 1; i >= 0; --i) {
        result[--count[source[i].key]] = source[i];
    }
    Swap(result, source);
}

int main() {
    Post post;
    TVector<Post> postList;

    while (scanf("%d\t%llu\n", &post.key, &post.data) == 2) {
        postList.Push(post);
    }

    CountingSort(postList);

    for (int i = 0; i < postList.Size(); ++i) {
        printf("%06d\t%llu\n", postList[i].key, postList[i].data);
    }
    return 0;
}
