#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>

using std::cout;
using std::endl;

template<typename ValType>
struct Node
{
    ValType val;
    Node* next;
};

template<class ValType>
class List
{
private:
    Node<ValType>* node;

public:
    List();
    List(ValType);
    List(const ValType*, size_t);
    List(List<ValType>&);
    ~List();

    void print();
    size_t getSize();
    bool isEmpty();
    void pushBack(ValType);
    void pushFront(ValType);
    void add(ValType, size_t);
    ValType popBack();
    ValType popFront();
    ValType pop(size_t);
    void revers();
    ValType getHead();
    ValType getTail();
    ValType getVal(size_t);

    List<ValType>& operator =(List<ValType>&);
    void operator +=(ValType);
    void operator +=(List<ValType>&);
    ValType operator [](size_t);
};

#include "list.cpp"

#endif // LIST_H_INCLUDED
