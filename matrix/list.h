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

    void pushBack(ValType data)
    {
        add(data, getSize());
    }

    void pushFront(ValType data)
    {
        add(data, 0);
    }

    void add(ValType data, size_t num)
    {
        if(!isEmpty())
        {
            node = new Node<ValType>;
            node->val = data;
            node->next = NULL;

            return;
        }

        Node<ValType>* buff = node;

        for(size_t i = 0; (i < num) && (buff->next); i++)
            buff = buff->next;

        Node<ValType>* tmp = new Node<ValType>;
        tmp->val = data;

        if(buff->next)
        {
            buff->next = tmp->next;
        }else
        {
            tmp->next = NULL;
        }

        buff->next = tmp;

        if(num == 1)
            node = buff;
    }

    void purgeBack()
    {
        purge(getSize());
    }

    void purgeFront()
    {
        purge(0);
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

struct Elem
{
    unsigned line;
    unsigned column;
    int val;
};

class Matrix
{
private:
    List<Elem*> elemList;
    size_t lines;
    size_t columns;

public:
    Matrix()
    {
        elemList = NULL;
        lines = 0;
        columns = 0;
    }

    Matrix(int arrMatrix[3][3], size_t lines, size_t columns)
    {
        Elem* elem;

        this->lines = lines;
        this->columns = columns;

        for(size_t i = 0; i < lines; i++)
            for(size_t j = 0; j < columns; j++)
                if(arrMatrix[i][j])
                {
                    elem = new Elem;
                    elem->line = i;
                    elem->column = j;
                    elem->val = arrMatrix[i][j];
                    elemList.pushBack(elem);
                }
    }

    void print()
    {
        Elem* tmp = elemList[0];
        size_t k = 0;

        for(size_t i = 0; i < lines; i++)
        {
            for(size_t j = 0; j < columns; j++)
                if(tmp && (i == tmp->line) && (j == tmp->column))
                {
                    cout << tmp->val << " ";

                    k++;
                    tmp = elemList[k];
                }else
                    cout << 0 << " ";

            cout << endl;
        }

        cout << endl;
    }

    void operator *=(int digit)
    {
        for(size_t i = 0; i < elemList.getSize(); i++)
        {
            elemList[i]->val *= digit;
        }
    }

    void operator +=(Matrix otherMatr)
    {
        if((this->lines != otherMatr.lines) || (this->columns != otherMatr.columns))
            return;

        for(size_t i = 0; i < otherMatr.elemList.getSize(); i++)
        {
            if((this->elemList[i]->line == otherMatr.elemList[i]->line) && (this->elemList[i]->column == otherMatr.elemList[i]->column))
                this->elemList[i]->val += otherMatr.elemList[i]->val;
            else
                this->elemList.add(otherMatr.elemList[i], i);
        }
    }
};

#endif // MATRIX_H_INCLUDED
