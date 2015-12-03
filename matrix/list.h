#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

template<typename ValType>
struct Node
{
    ValType val;
    Node* next;
};

template<typename ValType>
class List
{
private:
    Node<ValType>* node;

public:
    List()
    {
        node = NULL;
    }

    List(ValType data)
    {
        node = new Node<ValType>;
        node->val = data;
        node->next = NULL;
    }

    List(ValType* data, size_t num)
    {
        if(num == 0)
            return;

        node = new Node<ValType>;
        node->val = data[0];
        node->next = NULL;

        if(num == 1)
            return;

        Node<ValType>* tmp = node;

        for(size_t i = 1; i < num; i++)
        {
            tmp->next = new Node<ValType>;
            tmp->next->val = data[i];
            tmp->next->next = NULL;
            tmp = tmp->next;
        }
    }

    List(List<ValType>& copyList)
    {
        if(!copyList.isEmpty())
            node = NULL;

        node = new Node<ValType>;
        node->val = copyList.node->val;
        node->next = copyList.node->next;

        if(copyList.getSize() == 1)
            return;

        Node<ValType>* tmp = copyList.node;
        Node<ValType>* buff = node;

        while(tmp)
        {
            buff = new Node<ValType>;
            buff->val = tmp->val;
            buff->next = tmp->next;
            tmp = tmp->next;
        }
    }

    ~List()
    {
        Node<ValType>* tmp;

        while(node)
        {
            tmp = node;
            node = node->next;

            delete(tmp);
        }
    }

    void print()
    {
        Node<ValType>* tmp = node;

        while(tmp)
        {
            cout << tmp->val << " ";
            tmp = tmp->next;
        }

        cout << endl;
    }

    void print(FILE* file)
    {
        if(!file)
            return;

        Node<ValType>* tmp = node;

        while(tmp)
        {
            fwrite(&tmp->val, sizeof(ValType), 1, file);
            tmp = tmp->next;
        }
    }

    void print(ofstream& stream)
    {
        if(!stream.is_open())
            return;

        Node<ValType>* tmp = node;

        while(tmp)
        {
            stream.write((char*)(&tmp->val), sizeof(ValType));
            tmp = tmp->next;
        }
    }

    size_t getSize()
    {
        size_t result = 0;
        Node<ValType>* tmp = node;

        while(tmp)
        {
            result++;
            tmp = tmp->next;
        }

        return result;
    }

    bool isEmpty()
    {
        return (node ? true : false);
    }

    void add(ValType data)
    {
        add(data, getSize());
    }

    void add(ValType data, size_t num)
    {
        if(num > getSize() + 1)
            return;

        Node<ValType>* tmp = node;
        Node<ValType>* buff = NULL;

        if(num == 1)
        {
            buff = tmp;
            tmp= new Node<ValType>;
            tmp->val = data;
            tmp->next = buff;
            node = tmp;

            return;
        }

        for(size_t i = 1; i < num - 1; i++)
            tmp = tmp->next;

        buff = tmp->next;
        tmp->next = new Node<ValType>;
        tmp->next->val = data;
        tmp->next->next = buff;
    }

    void purge()
    {
        purge(getSize());
    }

    void purge(size_t num)
    {
        if(!isEmpty() || (num > getSize()))
            return;

        if(num == 1)
        {
            delete(node);

            return;
        }

        Node<ValType>* tmp = node;
        Node<ValType>* buff = NULL;

        for(size_t i = 1; i < num - 1; i++)
            tmp = tmp->next;

            buff = tmp->next->next;
            delete(tmp->next);
            tmp->next = buff;
    }

    void revers()
    {
        if(!isEmpty())
            return;

        Node<ValType>* tmp = node;
        Node<ValType>* buff = tmp;

        while(tmp->next)
            tmp = tmp->next;

        node = tmp;

        do
        {
            tmp = buff;

            while(tmp->next->next)
            {
                tmp = tmp->next;
            }

            tmp->next->next = tmp;
            tmp->next = 0;
        }while(tmp != buff);
    }

    ValType getHead()
    {
        return getVal(1);
    }

    ValType getTail()
    {
        return getVal(getSize());
    }

    ValType getVal(size_t num)
    {
        if(!isEmpty() || (num > getSize()) || (num == 0))
            return 0;

        Node<ValType>* tmp = node;

        for(size_t i = 1; i < num; i++)
            tmp = tmp->next;

        return tmp->val;
    }

    void operator +=(ValType data)
    {
        add(data);
    }

    void operator +=(List<ValType>& otherList)
    {
        if(!isEmpty())
        {
            node = otherList.node;

            return;
        }

        Node<ValType>* tmp = node;

        while(tmp->next)
            tmp = tmp->next;

        tmp->next = otherList.node;
    }

    ValType operator [](size_t num)
    {
        return getVal(num + 1);
    }
};

#endif // MATRIX_H_INCLUDED
