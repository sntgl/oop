#pragma once

#include "iterator.h"

template<typename T>
Iterator<T>::Iterator()
{
    ptr.lock() = nullptr;
}

template<typename T>
Iterator<T>::Iterator(const std::shared_ptr<Node<T>> &node)
{
    ptr = node;
}

template<typename T>
Iterator<T>::Iterator(const std::weak_ptr<Node<T>> &node)
{
    if (node.expired())
        throw PointerExpired(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    ptr = node;
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &iterator)
{
    iterator.check_expired();
    ptr = iterator.ptr.lock();
}

template<typename T>
Iterator<T>::operator bool() const
{
    return ptr.lock() != nullptr and !ptr.expired();
}

template<typename T>
bool Iterator<T>::is_valid() const
{
    return ptr.lock() != nullptr and !ptr.expired();
}

template<typename T>
Iterator<T> &Iterator<T>::operator++()
{
    check_expired();
    next();
    return *this;
}

template<typename T>
void Iterator<T>::next()
{
    check_expired();
    ptr = ptr.lock()->get_next();
}

template<typename T>
const Iterator<T> Iterator<T>::operator++(int)
{
    check_expired();
    auto temp = Iterator<T>(*this);
    next();
    return temp;
}

template<typename T>
T *Iterator<T>::operator->()
{
    check_expired();
    return &(ptr.lock()->get_value());
}

template<typename T>
T& Iterator<T>::operator*()
{
    check_expired();
    return ptr.lock()->get_value();
}

template<class T_>
std::ostream &operator<<(std::ostream &os, const Iterator<T_> &iterator)
{
    iterator.check_expired();
    os << iterator.ptr.lock()->get_value();
    return os;
}

template<typename T>
Node<T> &Iterator<T>::get_next_node()
{
    return *(ptr.lock().get()->get_next());
}

template<typename T>
Node<T> & Iterator<T>::get_node()
{
    return *(ptr.lock().get());
}

template<typename T>
Node<T> *Iterator<T>::get_next_node_ptr()
{
    return ptr.lock().get()->get_next().get();
}

template<typename T>
Node<T> *Iterator<T>::get_node_ptr()
{
    return ptr.lock().get();
}

template<typename T>
Iterator<T> Iterator<T>::operator+(const int &count)
{
    check_expired();
    Iterator<T> temp(*this);
    for (int i = 0; i < count; ++i)
        temp.next();
    return temp;
}

template<typename T>
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &iterator)
{
    check_expired();
    iterator.check_expired();
    ptr = iterator.ptr.lock();
    return *this;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T> &iterator) const
{
    check_expired();
    iterator.check_expired();
    return ptr.lock() != iterator.ptr.lock();
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T> &iterator) const
{
    check_expired();
    iterator.check_expired();
    return ptr.lock() == iterator.ptr.lock();
}

template<typename T>
void Iterator<T>::check_expired() const
{
    if (is_valid() && ptr.expired())
        throw PointerExpired(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
}

template<typename T>
const T *Iterator<T>::operator->() const
{
    check_expired();
    return &(ptr.lock()->get_value());
}

template<typename T>
const T &Iterator<T>::operator*() const
{
    check_expired();
    return ptr.lock()->get_value();
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T> &&iterator)
{
    ptr = iterator.ptr.lock();
}
