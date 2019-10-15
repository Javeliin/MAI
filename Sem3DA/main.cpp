#include <stdio.h>
#include <algorithm>
#include <cassert>


struct Post {
    unsigned long long int value;
    int key;
};

template <typename T>
class vector {
public:
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    vector():
        already_used_(0), storage_size_(0), storage_(nullptr)
    {
    }

    vector(int size, const value_type& default_value = value_type()):
        vector()
    {
        assert(size >= 0);

        if (size == 0)
            return;

        already_used_ = size;
        storage_size_ = size;
        storage_ = new value_type[size];

        std::fill(storage_, storage_ + already_used_, default_value);
    }

    int size() const
    {
        return already_used_;
    }

    bool empty() const
    {
        return size() == 0;
    }

    iterator begin() const
    {
        return storage_;
    }

    iterator end() const
    {
        if (storage_)
            return storage_ + already_used_;

        return nullptr;
    }

    friend void swap(vector& lhs, vector& rhs)
    {
        using std::swap;

        swap(lhs.already_used_, rhs.already_used_);
        swap(lhs.storage_size_, rhs.storage_size_);
        swap(lhs.storage_, rhs.storage_);
    }

    vector& operator=(vector other)
    {
        swap(*this, other);
        return *this;
    }

    vector(const vector& other):
        vector()
    {
        vector next(other.storage_size_);
        next.already_used_ = other.already_used_;

        if (other.storage_ )
            std::copy(other.storage_, other.storage_ + other.storage_size_,
                      next.storage_);

        swap(*this, next);
    }

    ~vector()
    {
        delete[] storage_;

        storage_size_ = 0;
        already_used_ = 0;
        storage_ = nullptr;
    }

    void push_back(const value_type& value)
    {
        if (already_used_ < storage_size_) {
            storage_[already_used_] = value;
            ++already_used_;
            return;
        }

        int next_size = 1;
        if (storage_size_)
            next_size = storage_size_ * 2;

        vector next(next_size);
        next.already_used_ = already_used_;

        if (storage_ )
            std::copy(storage_, storage_ + storage_size_, next.storage_);

        next.push_back(value);
        swap(*this, next);
    }

    const value_type& at(int index) const
    {
        if (index < 0 || index > already_used_)
            throw std::out_of_range("You are doing this wrong!");

        return storage_[index];
    }

    value_type& at(int index)
    {
        const value_type& elem = const_cast<const vector*>(this)->at(index);
        return const_cast<value_type&>(elem);
    }

    const value_type& operator[](int index) const
    {
        return at(index);
    }

    value_type& operator[](int index)
    {
        return at(index);
    }

private:
    int already_used_;
    int storage_size_;
    value_type* storage_;
};

const int RANGE = 1000000;

void Sorrt(vector<Post>& source);

int main() {
    vector <Post> postList;
    Post tmp;

    while (scanf("%d\t%llu\n", &tmp.key, &tmp.value) == 2) {
        postList.PushBack(tmp);
    }

    Sorrt(postList);

    for (int i = 0; i < postList.size(); ++i) {
        if (postList[i].key < 10) {
            printf("00000%d\t%llu\n", postList[i].key, postList[i].value);
        } else if (postList[i].key < 100) {
            printf("0000%d\t%llu\n", postList[i].key, postList[i].value);
        } else if (postList[i].key < 1000) {
            printf("000%d\t%llu\n", postList[i].key, postList[i].value);
        } else if (postList[i].key < 10000) {
            printf("00%d\t%llu\n", postList[i].key, postList[i].value);
        } else if (postList[i].key < 100000) {
            printf("0%d\t%llu\n", postList[i].key, postList[i].value);
        } else {
            printf("%d\t%llu\n", postList[i].key, postList[i].value);
        }
    }
    return 0;
}

void Sorrt(vector<Post>& source) {
    int count[RANGE]{0};
    vector <Post> result(source.size());

    for (int i = 0; i < source.size(); ++i) {
        ++count[source[i].key];
    }

    for (int i = 1; i < RANGE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = source.size() - 1; i >= 0; --i) {
        result[--count[source[i].key]] = source[i];
    }
    swap(result, source);
}
