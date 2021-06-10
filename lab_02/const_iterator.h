#pragma once
#include <iterator>
#include <memory>
#include "node.h"

template<typename T>
class ConstIterator: std::iterator<std::input_iterator_tag, Node<T>>
{
public:
    ConstIterator(); //конструктор - пустое создание
    explicit ConstIterator(const std::shared_ptr<Node<T>> &node); //конструктор - на основе shared_ptr
    explicit ConstIterator(const std::weak_ptr<Node<T>> &node); //конструктор - на основе weak_ptr
    ConstIterator(const ConstIterator<T> &iterator); //конструктор - на основе итератора
    explicit ConstIterator(const Iterator<T> &&iterator); //конструктор - на основе итератора

    void check_expired() const;
    operator bool() const; //перегрузка bool - проверка на валидность
    bool is_valid() const; //проверка на валидность
    void next(); //переход к следующему элементу

    ConstIterator<T> operator +(int &count);
    ConstIterator<T> &operator ++(); //pre-increment
    const ConstIterator<T> operator ++(int); //post-increment
    ConstIterator<T> &operator = (const ConstIterator<T> &iterator);

    bool operator !=(const ConstIterator<T> &iterator) const;
    bool operator ==(const ConstIterator<T> &iterator) const;

    const Node<T> &get_next_node();
    const Node<T> &get_node();
    const Node<T> *get_next_node_ptr();
    const Node<T> *get_node_ptr();

    T operator ->();
    const T operator ->() const;
    T& operator *();
    const T& operator *() const;



    template<class T_>
    friend std::ostream &operator<<(std::ostream &os, const ConstIterator<T_> &iterator);

private:
    std::weak_ptr<Node<T>> ptr;
};

#include "const_iterator.hpp"