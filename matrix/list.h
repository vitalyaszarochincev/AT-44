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

    size_t size()
    {
        size_t size = 0;
        Node<ValType>* tmp = node;

        while(tmp)
        {
            size++;
            tmp = tmp->next;
        }

        return size;
    }

    bool isEmpty()
    {
        return (node ? true : false);
    }

    void add(ValType data)
    {
        if(!isEmpty())
        {
            node = new Node<ValType>;
            node->val = data;
            node->next = NULL;
        }else
        {
            Node<ValType>* tmp = node;

            while(tmp->next)
                tmp = tmp->next;

            tmp->next = new Node<ValType>;
            tmp->next->val = data;
            tmp->next->next = NULL;
        }
    }

    void add(ValType data, size_t num)
    {
        if(num > size())
        {
            add(data);
            return;
        }

        Node<ValType>* tmp = node;
        Node<ValType>* buff;

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

    void operator +=(ValType data)
    {
        add(data);
    }

/*    void operator +=(List<ValType> list)
    {
        if(!isEmpty())
        {
            node = list.node;

            return;
        }

        Node<ValType>* tmp = node;

        while(tmp->next)
            tmp = tmp->next;

        tmp->next = list.node;
    }*/
};

#endif // MATRIX_H_INCLUDED
