#ifndef _STACK_H_
#define _STACK_H_

#include <algorithm>
#include <memory>
#include <iostream>


template <typename T>
class Stack {
public:
    using velueType = T;
    using iterator = velueType*;

    Stack() {
        top = 0;
        size = 0;
        storage = nullptr;
    }

    Stack(int newSize):
        Stack()
    {
        if (newSize < 0) {
            throw -1;
        } else if (newSize == 0) {
            return;
        }

        top = newSize;
        size = newSize;
        storage = std::make_unique<velueType[]>(size);
    }

    iterator Begin() const {
        return storage.get();
    }

    iterator End() const {
        if (storage.get()) {
            return storage.get() + top;
        }
        return nullptr;
    }

    int Size() const {
        return top;
    }

    bool IsEmpty() const {
        return Size() == 0;
    }

    void Swap(Stack& st1, Stack& st2) {
        std::swap(st1.size, st2.size);
        std::swap(st1.top, st2.top);
        std::swap(st1.storage, st2.storage);
    }

    void Push(const velueType& velue) {
        if (top < size) {
            storage[top] = velue;
            ++top;
            return;
        }

        int newSize;
        if (size) {
            newSize = size * 2;
        }
        Stack<T> newStack(newSize);
        newStack.top = top;

        if (storage.get()) {
            copy(storage.get(), storage.get() + size, newStack.storage.get());
        }
        newStack.Push(velue);
        Swap(*this, newStack);
    }

    velueType& Pop() {
        if (top) {
            return storage[top--];
        }
        throw -2;
    }

    velueType& Top() const {
        if (top) {
            return storage[top];
        }
        throw -2;
    }

    void Print() {
        std::for_each(Begin(), End(), [](iterator& key) {
            PrintFigure(*key);
            putchar('\n');
        });
    }

    Stack& operator=(Stack newStack)  {
        Swap(*this, newStack);
        return *this;
    }

    ~Stack() {}


private:
    int size, top;
    std::unique_ptr<velueType[]> storage;
};

#endif