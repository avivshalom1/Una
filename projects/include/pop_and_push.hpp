/************************************************
* Developer:      Aviv Shalom                   *
* Version:        1.0                           *   
* Date:           08.03.23                      *   
* Description:    Zemingo Home Assignment (.hpp)*
*************************************************/
#ifndef __POP_AND_PUSH__
#define __POP_AND_PUSH__

#include <functional>
#include <iostream>
#include <semaphore>
#include <mutex>

#include "utils.hpp"

namespace ilrd
{

/********************* PUSH AND POP ABSTRACT CLASS ***************/
template <typename T>
class PushAndPop : private ilrd::noncopyable
{
public:
    PushAndPop(std::function<bool(T lhs, T rhs)> cmpFunc = std::less<T>());
    virtual void Push(T value) = 0;
    virtual T Pop() = 0;
    ~PushAndPop();

protected:

    class Node
    {
    public:
        Node(T value, Node *prev = nullptr, Node *next = nullptr);
        ~Node();
 
        template <typename U>
        friend class QuickPop; 

        template <typename U>
        friend class QuickPush; 

        T m_value;
        Node *m_next;
        Node *m_prev;
    };

    size_t m_size;
    std::function<bool(T, T)> m_cmpFunc;
    Node *m_head;
    std::mutex m_mutex;
    std::counting_semaphore<std::__semaphore_impl::_S_max> m_sem;
};

template <typename T>
PushAndPop<T>::PushAndPop(std::function<bool(T lhs, T rhs)> cmpFunc) : 
m_size(0),
m_cmpFunc(cmpFunc),
m_head(nullptr),
m_sem(m_size)
{

}

template <typename T>
PushAndPop<T>::~PushAndPop()
{
    Node *temp = m_head;

    while(m_head)
    {
        temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
} 

/********************* NODE ***************/
template <typename T>
inline PushAndPop<T>::Node::Node(T value, Node* prev, Node* next) :
m_value(value),
m_next(next),
m_prev(prev)
{
} 

template <typename T>
PushAndPop<T>::Node::~Node()
{
}

/********************* QUICK POP ***************/
template <typename T>
class QuickPop : public PushAndPop<T>
{
public:
    QuickPop(std::function<bool(T lhs, T rhs)> cmpFunc = std::less<T>());
    T Pop();
    void Push(T value);
};

template <typename T>
inline QuickPop<T>::QuickPop(std::function<bool(T lhs, T rhs)> cmpFunc) : PushAndPop<T>(cmpFunc)
{
    
}
 
template <typename T>
inline T QuickPop<T>::Pop()
{
    this->m_sem.acquire();

    std::lock_guard<std::mutex> lock(this->m_mutex);

    typename PushAndPop<T>::Node *toDelete = this->m_head;

    T toReturn = toDelete->m_value;

    typename PushAndPop<T>::Node *newHead = this->m_head->m_next;

    this->m_head->m_prev = nullptr;
    this->m_head->m_next = nullptr;

    this->m_head = newHead;
    delete toDelete;
    this->m_size--;

    return toReturn;
}

template <typename T>
inline void QuickPop<T>::Push(T value)
{
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if(!this->m_head)
    {
        this->m_head = new PushAndPop<T>::Node(value);
    }

    else
    {
        typename PushAndPop<T>::Node *curr = this->m_head;

        while(this->m_cmpFunc(value, curr->m_value) && curr->m_next )
        {
            curr = curr->m_next;
        }
        
        typename PushAndPop<T>::Node *temp = curr->m_prev;

        curr->m_prev = new PushAndPop<T>::Node(value, temp, curr);

        if(temp)
        {
            temp->m_next = curr->m_prev;
        }

        else
        {
            this->m_head = curr->m_prev;
        }
    }

    this->m_size++;
    this->m_sem.release();

}

/********************* QUICK PUSH ***************/
template <typename T>
class QuickPush : public PushAndPop<T>
{
public:
    QuickPush(std::function<bool(T lhs, T rhs)> cmpFunc = std::less<T>());
    T Pop();
    void Push(T value);
};

template <typename T>
inline QuickPush<T>::QuickPush(std::function<bool(T lhs, T rhs)> cmpFunc) : PushAndPop<T>(cmpFunc)
{

}
 
template <typename T>
inline T QuickPush<T>::Pop()
{
    this->m_sem.acquire();

    std::lock_guard<std::mutex> lock(this->m_mutex);

    T max = this->m_head->m_value;

    typename PushAndPop<T>::Node *curr = this->m_head;
    typename PushAndPop<T>::Node *maxNode = this->m_head;

    while(curr)
    {
        if(curr->m_value > max)
        {
            max = curr->m_value;
            maxNode = curr;
        } 

        curr = curr->m_next;
    }

    if(maxNode->m_next)
    {
        maxNode->m_prev->m_next = maxNode->m_next;
        maxNode->m_next->m_prev = maxNode->m_prev;
        
        maxNode->m_prev = nullptr;
        maxNode->m_next = nullptr;

    }

    else if(maxNode->m_prev)
    {
        maxNode->m_prev->m_next = nullptr;
        maxNode->m_prev = nullptr;
    }
    
    else
    {
        maxNode->m_next = nullptr;
        this->m_head = this->m_head->m_next;
    }

    delete maxNode;
    this->m_size--;

    return max;
}

template <typename T>
inline void QuickPush<T>::Push(T value)
{
    std::lock_guard<std::mutex> lock(this->m_mutex);

    if(!this->m_head)
    {
        this->m_head = new PushAndPop<T>::Node(value);
    }

    else
    {
        

        typename PushAndPop<T>::Node *curr = this->m_head;

        while(curr->m_next)
        {
            curr = curr->m_next;
        }
        
        curr->m_next = new PushAndPop<T>::Node(value, curr, nullptr);
    }

    this->m_size++;
    this->m_sem.release();
}

}
#endif //__POP_AND_PUSH__