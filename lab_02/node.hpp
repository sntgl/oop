#pragma once
#include <memory>
#include "node.h"


template<typename T>
Node<T>::Node()
{
    this->next = nullptr;
}

template<typename T>
Node<T>::Node(T const &data)
{
    this->data = data;
    this->next = nullptr;
}

template<typename T>
Node<T>::Node(Node<T> &node)
{
    this->data = node.data;
    this->next = node.next;
}

template<typename T>
std::shared_ptr<Node<T>> Node<T>::get_next()
{
    return next;
}

template<typename T>
void Node<T>::set_next(const std::shared_ptr<Node<T>> &next_node)
{
    this->next = next_node;
}

template<typename T>
void Node<T>::set_next()
{
    this->next = nullptr;
}

template<typename T>
void Node<T>::set(const T &new_data)
{
    this->data = new_data;
}

template<typename T>
T &Node<T>::get_value()
{
    return data;
}

template<typename T>
bool Node<T>::operator!=(const std::shared_ptr<Node<T>> &node) const
{
    return this != node;
}

template<typename T>
bool Node<T>::operator==(const std::shared_ptr<Node<T>> &node) const
{
    return this == node;
}

template<typename T>
void Node<T>::set_next(const Node<T> &new_next)
{
    std::shared_ptr<Node<T>> new_ptr(new_next);
    this->next = new_ptr;
}

template<typename T>
const T &Node<T>::get() const
{
    return data;
}

template<typename T>
Node<T>::Node(Node<T> &&node)
{
    next = node.next;
    data = node.data;
}


