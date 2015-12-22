#ifndef LIST_CPP_INCLUDED
#define LIST_CPP_INCLUDED

#include "list.h"
#include <fstream>

using std::endl;

///////////////////////////////////////List()/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>::List():m_node(NULL){}

///////////////////////////////////////List(ValType)/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>::List(ValType data):m_node(new Node<ValType>)
{
    this->m_node->val = data;
    this->m_node->next = NULL;
}

///////////////////////////////////////List(const ValType*, size_t)/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>::List(const ValType* data, size_t num)
{
    if(num == 0)
        return;

    this->m_node = new Node<ValType>;
    this->m_node->val = data[0];
    this->m_node->next = NULL;

    if(num == 1)
        return;

    Node<ValType>* tmp = this->m_node;

    for(size_t i = 1; i < num; i++)
    {
        tmp->next = new Node<ValType>;
        tmp->next->val = data[i];
        tmp->next->next = NULL;
        tmp = tmp->next;
    }
}

///////////////////////////////////////List(List<ValType>&)/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>::List(List<ValType>& copyList)
{
    if(!copyList.isEmpty())
        this->m_node = NULL;

    this->m_node = new Node<ValType>;
    this->m_node->val = copyList.m_node->val;
    this->m_node->next = NULL;

    if(copyList.getSize() == 1)
        return;

    Node<ValType>* tmp = copyList.m_node->next;
    Node<ValType>* buff = this->m_node;

    while(tmp)
    {
        buff->next = new Node<ValType>;
        buff->next->val = tmp->val;
        buff->next->next = NULL;
        buff = buff->next;
        tmp = tmp->next;
    }
}

///////////////////////////////////////~List()/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>::~List()
{
    Node<ValType>* tmp;

    while(this->m_node)
    {
        tmp = this->m_node;
        this->m_node = this->m_node->next;
        delete(tmp);
    }
}

///////////////////////////////////////print()/////////////////////////////////////////////////////////

template<class ValType>
void List<ValType>::print()
{
    std::ofstream testFile("C:\\Users\\vitalii\\Documents\\projects\\matrix\\data\\test.txt", std::ios::app | std::ios::out);
    if(!isEmpty())
    {
        testFile << "<empty>" << endl;
        return;
    }

    Node<ValType>* tmp = this->m_node;

    while(tmp)
    {
        testFile << tmp->val << " ";
        tmp = tmp->next;
    }

    testFile << endl;
}

///////////////////////////////////////getSize()/////////////////////////////////////////////////////////

template<class ValType>
size_t List<ValType>::getSize()
{
    size_t result = 0;
    Node<ValType>* tmp = this->m_node;

    while(tmp)
    {
        result++;
        tmp = tmp->next;
    }

    return result;
}

///////////////////////////////////////isEmpty()/////////////////////////////////////////////////////////

template<class ValType>
bool List<ValType>::isEmpty()
{
    return (this->m_node ? true : false);
}

///////////////////////////////////////pushBack(ValType)/////////////////////////////////////////////////////////

template<class ValType>
void List<ValType>::pushBack(ValType data)
{
    add(data, getSize() + 1);
}

///////////////////////////////////////pushFront(ValType)/////////////////////////////////////////////////////////

template<class ValType>
void List<ValType>::pushFront(ValType data)
{
    add(data, 1);
}

///////////////////////////////////////add(ValType, size_t)/////////////////////////////////////////////////////////

template<class ValType>
void List<ValType>::add(ValType data, size_t num)
{
    if(num > this->getSize() + 1)
        return;

    if(num == 1)
    {
        if(!isEmpty())
        {
            this->m_node = new Node<ValType>;
            this->m_node->val = data;
            this->m_node->next = NULL;
            return;
        }else
        {
            Node<ValType>* tmp = this->m_node;
            this->m_node = new Node<ValType>;
            this->m_node->val = data;
            this->m_node->next = tmp;
            return;
        }
    }

    Node<ValType>* buff = this->m_node;

    for(size_t i = 1; (i < num - 1) && (buff->next); i++)
        buff = buff->next;

    Node<ValType>* tmp = new Node<ValType>;
    tmp->val = data;

    if(buff->next)
        tmp->next = buff->next;
    else
        tmp->next = NULL;

    buff->next = tmp;

    if(num == 1)
        this->m_node = buff;
}

///////////////////////////////////////popBack()/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::popBack()
{
    return pop(getSize());
}

///////////////////////////////////////popFront()/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::popFront()
{
    return pop(1);
}

///////////////////////////////////////pop(size_t)/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::pop(size_t num)
{
    if(!this->isEmpty() || (num > this->getSize() + 1))
        return 0;

    if(num == 1)
    {
        Node<ValType>* tmp = this->m_node->next;
        ValType result = this->m_node->val;
        delete(this->m_node);
        this->m_node = tmp;
        return result;
    }

    Node<ValType>* tmp = this->m_node;
    Node<ValType>* buff = NULL;

    for(size_t i = 1; i < num - 1; i++)
        tmp = tmp->next;

    ValType result = tmp->next->val;

    buff = tmp->next;

    tmp->next = buff->next;

    delete(buff);

    return result;
}

///////////////////////////////////////revers()/////////////////////////////////////////////////////////

template<class ValType>
void List<ValType>::revers()
{
    if(!this->isEmpty())
        return;

    Node<ValType>* tmp = this->m_node;
    Node<ValType>* buff = tmp;

    while(tmp->next)
        tmp = tmp->next;

    this->m_node = tmp;

    do
    {
        tmp = buff;

        while(tmp->next->next)
            tmp = tmp->next;

        tmp->next->next = tmp;
        tmp->next = 0;
    }while(tmp != buff);
}

///////////////////////////////////////getHead()/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::getHead()
{
    return this->getVal(1);
}

///////////////////////////////////////getTail()/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::getTail()
{
    return this->getVal(getSize());
}

///////////////////////////////////////getVal(size_t)/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::getVal(size_t num)
{
    if(!this->isEmpty() || (num > this->getSize()) || (num == 0))
        return 0;

    Node<ValType>* tmp = this->m_node;

    for(size_t i = 1; i < num; i++)
        tmp = tmp->next;

    return tmp->val;
}

///////////////////////////////////////operator =(List<ValType&>)/////////////////////////////////////////////////////////

template<class ValType>
List<ValType>& List<ValType>::operator =(List<ValType>& copyList)
{
    Node<ValType>* tmp;

    while(this->m_node)
    {
        tmp = this->m_node;
        this->m_node = this->m_node->next;
        delete(tmp);
    }

    if(!copyList.isEmpty())
        this->m_node = NULL;

    this->m_node = new Node<ValType>;
    this->m_node->val = copyList.m_node->val;
    this->m_node->next = NULL;

    if(copyList.getSize() == 1)
        return *this;

    tmp = copyList.m_node->next;
    Node<ValType>* buff = this->m_node;

    while(tmp)
    {
        buff->next = new Node<ValType>;
        buff->next->val = tmp->val;
        buff->next->next = NULL;
        buff = buff->next;
        tmp = tmp->next;
    }

    return *this;
}

///////////////////////////////////////operator [](size_t)/////////////////////////////////////////////////////////

template<class ValType>
ValType List<ValType>::operator [](size_t num)
{
    return this->getVal(num + 1);
}

#endif // LIST_CPP_INCLUDED
