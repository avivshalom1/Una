/************************************************
* Developer:      Aviv Shalom              	    *
* Version:        1.0                           *   
* Date:           08.03.23                      *   
* Description:    Zemingo Home Assignment (.hpp) *
*************************************************/
#ifndef __POP_AND_PUSH__
#define __POP_AND_PUSH__

#include <functional>
#include <iostream>

#include "utils.hpp"

namespace ilrd
{

/********************* NODE ***************/
template <typename T>
class Node
{
public:
    Node(T value, Node<T> *prev = nullptr, Node<T> *next = nullptr);
    T GetVal();
    ~Node();

    template <typename U>
    friend class QuickPopDS;

private:
    T m_value;
    Node<T> *m_next;
    Node<T> *m_prev;
};

template <typename T>
Node<T>::Node(T value, Node<T> *prev, Node<T> *next) : 
m_value(value),
m_next(next),
m_prev(prev)
{}

template <typename T>
T Node<T>::GetVal()
{
    return m_value;
}

template <typename T>
Node<T>::~Node()
{

}

/********************* QUICK POP ***************/
template <typename T>
class QuickPopDS : private ilrd::noncopyable
{
public:
    QuickPopDS(std::function<bool(T lhs, T rhs)> cmpFunc = std::less<T>());
    T QuickPopDSPop();
    void QuickPopDSPush(T value);
    ~QuickPopDS();

private:
    size_t m_size;
    std::function<bool(T, T)> m_cmpFunc;
    Node<T> *m_head;
};

template <typename T>
inline QuickPopDS<T>::QuickPopDS(std::function<bool(T lhs, T rhs)> cmpFunc) : 
m_size(0),
m_cmpFunc(cmpFunc),
m_head(nullptr)
{
    std::cout << "Ctor" << std::endl;
}

template <typename T>
inline T QuickPopDS<T>::QuickPopDSPop()
{
    Node<T> *toDelete = m_head;
    T toReturn = toDelete->m_value;

    Node<T> *newHead = m_head->m_next;

    m_head->m_prev = nullptr;
    m_head->m_next = nullptr;

    m_head = newHead;
    delete toDelete;
    m_size--;

    return toReturn;
}

template <typename T>
inline void QuickPopDS<T>::QuickPopDSPush(T value)
{
    std::cout << "Push" << std::endl;

    if(!m_head)
    {
        m_head = new Node<T>(value);
    }

    else
    {
        Node<T> *curr = m_head;

        while(m_cmpFunc(curr->m_value, value) && curr->m_next )
        {
            std::cout << "while" << std::endl;
            curr = curr->m_next;
        }
        
        Node<T> *temp = curr->m_next;

        curr->m_next = new Node<T>(value, curr, temp);

        if(temp)
        {
            temp->m_prev = curr->m_next;
        }
    }

    m_size++;
}

template <typename T>
inline QuickPopDS<T>::~QuickPopDS()
{}

/********************* QUICK PUSH ***************/


}
#endif //__POP_AND_PUSH__