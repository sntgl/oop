#pragma once

#include <memory>
#include "base.h"
#include "error.h"
#include "iterator.h"
#include "const_iterator.h"


template<typename T>
class List : public Base
{
public:
    List() noexcept; //конструктор - создание пустого

    explicit List(const List<T> &list); //конструктор - копирование
    List<T> &operator=(const List<T> &list) noexcept; //переместить к конструкторам

    List(List<T> &&list) noexcept; //конструктор - временный объект - перенос
    List<T> &operator=(List<T> &&list) noexcept;

    List(const T *arr, const int &arr_size); //конструктор - из указателя на массив
    List(std::initializer_list<T> nodes); //конструктор - создание из списка

    template<typename Iter>
    List(Iter &from, Iter &to);
    ~List() override = default; //деструктор

    bool is_empty() const noexcept override;
    void clear() override;

    Iterator<T> add(const T &data); //to tail
    Iterator<T> add(const List<T> &list);
    Iterator<T> add(T *const arr, const int &arr_size);
    template<class Iter>
    Iterator<T> add(Iter from, Iter &to);

    Iterator<T> push(const T &data);
    Iterator<T> push(const List<T> &list);
    Iterator<T> push(T *const arr, const int &arr_size);

    template<class Iter>
    Iterator<T> insert(Iter &iterator, const T &data);
    template<class Iter>
    Iterator<T> insert(Iter &iterator, const List<T> &list);
    template<class Iter>
    Iterator<T> insert(Iter &iterator, Iter from, Iter &to);

    T pop(); //забирает элемент из начала списка
    T pop(Iterator<T> &iterator);

    template<class Iter>
    void remove(Iter from, Iter to);
    template<class Iter>
    void remove(Iter from);

    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;
    ConstIterator<T> begin() const noexcept; //если данные const
    ConstIterator<T> end() const noexcept;
    ConstIterator<T> const_begin() const noexcept;
    ConstIterator<T> const_end() const noexcept;


    operator bool() const noexcept;

    bool operator==(const List<T> &list) const noexcept; //может быть неточным, тк нет компаратора
    bool operator!=(const List<T> &list) const noexcept; //может быть неточным, тк нет компаратора

    List<T> operator+(const List<T> &r_list) ; //const
    List<T> operator+(const T &data); //const
    List<T> &operator+=(const List<T> &list);
    List<T> &operator+=(const T &data);

    template<class T_>
    friend std::ostream &operator << (std::ostream &os, const List<T_> &list);


protected:
    Iterator<T> add(const std::shared_ptr<Node<T>> &node_ptr); //добавляет элемент в конец спика
    Iterator<T> push(const std::shared_ptr<Node<T>> &node_ptr); //добавляет элемент в начало спика
    std::shared_ptr<Node<T>> create_shared_from_data(const T &data);

    template<class Iter>
    Iterator<T> check_iterator(Iter &in_iterator);

private:
    size_t size;
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
};

#include "list.hpp"