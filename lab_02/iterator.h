#pragma once
#include <iterator>
#include <memory>
#include "node.h"

template<typename T>
class Iterator: std::iterator<std::input_iterator_tag, Node<T>>
{
public:
    Iterator(); //конструктор - пустое создание
    explicit Iterator(const std::shared_ptr<Node<T>> &node); //конструктор - на основе shared_ptr
    explicit Iterator(const std::weak_ptr<Node<T>> &node); //конструктор - на основе weak_ptr
    Iterator(const Iterator<T> &iterator); //конструктор - на основе итератора
    Iterator(const Iterator<T> &&iterator); //конструктор - на основе итератора

    void check_expired() const;
    bool is_valid() const; //проверка на валидность
    virtual void next(); //переход к следующему элементу


    Iterator<T> operator +(const int &count);
    Iterator<T> &operator ++(); //pre-increment
    const Iterator<T> operator ++(int); //post-increment
    Iterator<T> &operator = (const Iterator<T> &iterator);

    bool operator !=(const Iterator<T> &iterator) const;
    bool operator ==(const Iterator<T> &iterator) const;

    Node<T> &get_next_node();
    Node<T> &get_node();
    Node<T> *get_next_node_ptr();
    Node<T> *get_node_ptr();

    operator bool() const; //перегрузка bool - проверка на валидность

    T *operator ->();
    const T *operator ->() const;
    T& operator *();
    const T& operator *() const;


    template<class T_>
    friend std::ostream& operator<<(std::ostream& os, const Iterator<T_> &iterator);

private:
    std::weak_ptr<Node<T>> ptr;
};

#include "iterator.hpp"