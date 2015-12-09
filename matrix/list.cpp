#ifndef LIST_CPP_INCLUDED
#define LIST_CPP_INCLUDED

#include "list.h"

template<class ValType>
List<ValType>::
List() :
node(NULL) {}

template<class ValType>
List<ValType>::
List(ValType data):
node(new Node<ValType>)
{
    node->val = data;
    node->next = NULL;
}

template<class ValType>
List<ValType>::
List(const ValType* data, size_t num)
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

template<class ValType>
List<ValType>::
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

template<class ValType>
List<ValType>::
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

template<class ValType>
void List<ValType>::
print()
{
    if(!isEmpty())
    {
        cout << "<empty>" << endl;
        return;
    }

    Node<ValType>* tmp = node;

    while(tmp)
    {
        cout << tmp->val << " ";
        tmp = tmp->next;
    }

    cout << endl;
}

template<class ValType>
size_t List<ValType>::
getSize()
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

template<class ValType>
bool List<ValType>::
isEmpty()
{
    return (node ? true : false);
}

template<class ValType>
void List<ValType>::
pushBack(ValType data)
{
    add(data, getSize() + 1);
}

template<class ValType>
void List<ValType>::
pushFront(ValType data)
{
    add(data, 1);
}

template<class ValType>
void List<ValType>::
add(ValType data, size_t num)
{
    if(num > getSize() + 1)
        return;

    if(num == 1)
    {
        if(!isEmpty())
        {
            node = new Node<ValType>;
            node->val = data;
            node->next = NULL;
            return;
        }else
        {
            Node<ValType>* tmp = node;
            node = new Node<ValType>;
            node->val = data;
            node->next = tmp;
            return;
        }
    }

    Node<ValType>* buff = node;

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
        node = buff;
}

template<class ValType>
ValType List<ValType>::
popBack()
{
    return pop(getSize() + 1);
}

template<class ValType>
ValType List<ValType>::
popFront()
{
    return pop(1);
}

template<class ValType>
ValType List<ValType>::
pop(size_t num)
{
    if(!isEmpty() || (num > getSize() + 1))
        return 0;

    if(num == 1)
    {
        Node<ValType>* tmp = node->next;
        ValType result = node->val;
        delete(node);
        node = tmp;
        return result;
    }

    Node<ValType>* tmp = node;
    Node<ValType>* buff = NULL;

    for(size_t i = 1; i < num - 1; i++)
        tmp = tmp->next;

    ValType result = tmp->val;

    if(tmp->next)
        if(tmp->next->next)
        {
            buff = tmp->next;
            buff->next = tmp->next->next;
        }

    delete(tmp);
    tmp = buff;
    return result;
}

template<class ValType>
void List<ValType>::
revers()
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
            tmp = tmp->next;

        tmp->next->next = tmp;
        tmp->next = 0;
    }while(tmp != buff);
}

template<class ValType>
ValType List<ValType>::
getHead()
{
    return getVal(1);
}

template<class ValType>
ValType List<ValType>::
getTail()
{
    return getVal(getSize());
}

template<class ValType>
ValType List<ValType>::
getVal(size_t num)
{
    if(!isEmpty() || (num > getSize()) || (num == 0))
        return 0;

    Node<ValType>* tmp = node;

    for(size_t i = 1; i < num; i++)
        tmp = tmp->next;

    return tmp->val;
}

template<class ValType>
List<ValType>& List<ValType>::
operator =(List<ValType>& copyList)
{
    Node<ValType>* tmp;

    while(this->node)
    {
        tmp = this->node;
        this->node = this->node->next;
        delete(tmp);
    }

    if(!copyList.isEmpty())
        this->node = NULL;

    this->node = new Node<ValType>;
    this->node->val = copyList.node->val;
    this->node->next = copyList.node->next;

    if(copyList.getSize() == 1)
        return;

    tmp = copyList.node;
    Node<ValType>* buff = node;

    while(tmp)
    {
        buff = new Node<ValType>;
        buff->val = tmp->val;
        buff->next = tmp->next;
        tmp = tmp->next;
    }
}

template<class ValType>
void List<ValType>::
operator +=(ValType data)
{
    add(data);
}

template<class ValType>
void List<ValType>::
operator +=(List<ValType>& otherList)
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

template<class ValType>
ValType List<ValType>::
operator [](size_t num)
{
    return getVal(num + 1);
}

#endif // LIST_CPP_INCLUDED
