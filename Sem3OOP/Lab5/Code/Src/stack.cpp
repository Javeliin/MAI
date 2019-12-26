#include <algorithm>
#include <memory>
#include <iostream>
#include "../Include/stack.hpp"


using namespace std;

template <typename T>
Stack<T>::Stack() {
    top = 0;
    size = 0;
    storage = nullptr;
}

template <typename T>
Stack<T>::Stack(int newSize):
    Stack<T>::Stack()
{
    if (newSize < 0) {
        throw -1;
    } else if (newSize == 0) {
        return;
    }

    top = newSize;
    size = newSize;
    storage = make_unique<velueType[]>(size);
}

template <typename T>
iterator Stack<T>::Begin() const {
    return storage.get();
}

template <typename T>
iterator Stack<T>::End() const {
    if (storage.get()) {
        return storage.get() + top;
    }
    return nullptr;
}

template <typename T>
int Stack<T>::Size() const {
    return top;
}

template <typename T>
bool Stack<T>::IsEmpty() const {
    return Size() == 0;
}

template <typename T>
void Stack<T>::Swap(Stack& st1, Stack& st2) {
    std::swap(st1.size, st2.size);
    std::swap(st1.top, st2.top);
    std::swap(st1.storage, st2.storage);
}

template <typename T>
void Stack<T>::Push(const velueType& velue) {
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

template <typename T>
T& Stack<T>::Pop() {
    if (top) {
        return storage[top--];
    }
    throw -2;
}

template <typename T>
T& Stack<T>::Top() const {
    if (top) {
        return storage[top];
    }
    throw -2;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack newStack) {
    Swap(*this, newStack);
    return *this;
}

template <typename T>
Stack<T>::~Stack() {
    top = 0;
    size = 0;
}
