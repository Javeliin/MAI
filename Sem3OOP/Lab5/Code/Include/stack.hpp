#ifndef _STACK_H_
#define _STACK_H_


template <typename T>
class Stack {
public:
    using velueType = T;
    using iterator = velueType*;

    Stack();
    Stack(int newSize);

    iterator Begin() const;
    iterator End() const;

    int Size() const;
    bool IsEmpty() const;
    void Swap(Stack& st1, Stack& st2);
    void Push(const velueType& velue);
    velueType& Pop();
    velueType& Top() const;
    void Print();

    Stack& operator=(Stack newStack);

    ~Stack();


private:
    int size, top;
    std::unique_ptr<velueType[]> storage;
};

#endif