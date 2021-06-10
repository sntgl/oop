#pragma once

#include <memory>

template<typename T>
class Node
{
public:
    Node(); //конструктор - пустое создание
    explicit Node(T const &data); //конструктор - создание на основе данных
    Node(Node<T> &node); //конструтор - копирование
    Node(Node<T> &&node); //конструтор - перенос

    void set(const T &data); //установка данных
    void set_next(const std::shared_ptr<Node<T>> &next); //установка следующего элемента
    void set_next(const Node<T> &next); //установка следующего элемента
    void set_next(); //установка пустого следующего элемента

    T &get_value(); //получение данных
    const T &get() const; //получение данных (неизменяемый)
    std::shared_ptr<Node<T>> get_next(); //получение следующего элемента

    bool operator!=(const std::shared_ptr<Node<T>> &node) const;
    bool operator==(const std::shared_ptr<Node<T>> &node) const;

private:
    T data;
    std::shared_ptr<Node<T>> next;
};

#include "node.hpp"