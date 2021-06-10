#pragma once

#include "const_iterator.h"

template<typename T>
ConstIterator<T>::ConstIterator()
{
    this->ptr.lock() = nullptr;
}

template<typename T>
ConstIterator<T>::ConstIterator(const std::shared_ptr<Node<T>> &node)
{
    this->ptr = node;
}

template<typename T>
ConstIterator<T>::ConstIterator(const std::weak_ptr<Node<T>> & node)
{
    this->ptr = node;
}

template<typename T>
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
}

template<typename T>
ConstIterator<T>::operator bool() const
{
    return is_valid();
}

template<typename T>
bool ConstIterator<T>::is_valid() const
{
    return ptr.lock() != nullptr and !ptr.expired();
}

template<typename T>
ConstIterator<T> &ConstIterator<T>::operator++()
{
    check_expired();
    next();
    return *this;
}

template<typename T>
void ConstIterator<T>::next()
{
    check_expired();
    ptr = ptr.lock()->get_next();
}

template<typename T>
const ConstIterator<T> ConstIterator<T>::operator++(int)
{
    check_expired();
    auto temp = ConstIterator<T>(*this);
    next();
    return temp;
}

template<typename T>
T ConstIterator<T>::operator->()
{
    check_expired();
    return this->ptr.lock()->get_value();
}

template<typename T>
const T ConstIterator<T>::operator->() const
{
    check_expired();
    return this->ptr.lock()->get_value();
}

template<typename T>
T& ConstIterator<T>::operator*()
{
    check_expired();
    return this->ptr.lock()->get_value(); //не работает
}

template<typename T>
const T& ConstIterator<T>::operator*() const
{
    check_expired();
    return this->ptr.lock()->get_value();
}


template<typename T>
ConstIterator<T> &ConstIterator<T>::operator=(const ConstIterator<T> &iterator)
{
    iterator.check_expired();
    ptr = iterator.ptr.lock();
    return *this;
}

template<typename T>
ConstIterator<T> ConstIterator<T>::operator+(int &count)
{
    check_expired();
    ConstIterator<T> &new_iterator(*this);
    for (int i = 0; i < count; ++i)
        new_iterator.next();
    return ConstIterator<T>();
}

template<typename T>
const Node<T> &ConstIterator<T>::get_next_node()
{
    check_expired();
    return *(ptr.lock().get()->get_next());
}

template<typename T>
const Node<T> &ConstIterator<T>::get_node()
{
    check_expired();
    return *(ptr.lock());
}

template<typename T>
const Node<T> *ConstIterator<T>::get_next_node_ptr()
{
    check_expired();
    return ptr.lock().get()->get_next().get();
}

template<typename T>
const Node<T> *ConstIterator<T>::get_node_ptr()
{
    check_expired();
    return ptr.lock().get();
}

template<typename T>
void ConstIterator<T>::check_expired() const
{
    if (ptr.lock() != nullptr && this->ptr.expired())
        throw PointerExpired(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
}


template<typename T>
bool ConstIterator<T>::operator!=(const ConstIterator<T> &iterator) const
{
    this->check_expired();
    iterator.check_expired();
    return this->ptr.lock() != iterator.ptr.lock();
}

template<typename T>
bool ConstIterator<T>::operator==(const ConstIterator<T> &iterator) const
{
    this->check_expired();
    iterator.check_expired();
    return this->ptr.lock() == iterator.ptr.lock();
}


template<class T_>
std::ostream &operator<<(std::ostream &os, const ConstIterator<T_> &iterator)
{
    iterator.check_expired();
    os << iterator.ptr.lock()->get_value();
    return os;
}

template<typename T>
ConstIterator<T>::ConstIterator(const Iterator<T> &&iterator)
{
    this->ptr = iterator.ptr;
}
