#pragma once

#include "list.h"

template<typename T>
List<T>::List() noexcept
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

template<typename T>
List<T>::List(List<T> const &list)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
    for (auto data: list) {
        add(data);
    }
}

template<typename T>
List<T>::List(std::initializer_list<T> nodes)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;

    for (auto node: nodes)
        add(node);
}

template<typename T>
List<T>::operator bool() const noexcept
{
    return !is_empty();
}

template<typename T>
void List<T>::clear()
{
    while (!is_empty())
        pop();
}

template<typename T>
List<T>::List(const T *arr, const int &arr_size)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    if (!arr)
        throw PointerError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    for (int i = 0; i < arr_size; ++i)
        add(*(arr + i));
}

template<typename T>
template<typename Iter>
List<T>::List(Iter &from, Iter &to)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
    for (; from != to + 1; from++)
    {
        add(*from);
    }
}

template<typename T>
Iterator<T> List<T>::add(const T &data)
{
    auto node = create_shared_from_data(data);
    return add(node);
}


template<typename T>
Iterator<T> List<T>::add(const std::shared_ptr<Node<T>> &node_ptr)
{
    if (!node_ptr)
        throw PointerError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    if (*this) {
        this->tail->set_next(node_ptr);
        this->tail = node_ptr;
    } else {
        this->head = node_ptr;
        this->tail = node_ptr;
    }
    this->size++;
    Iterator<T> iterator(node_ptr);
    return iterator;
}

template<typename T>
Iterator<T> List<T>::begin() noexcept
{
    return Iterator<T>(this->head);
}

template<typename T>
Iterator<T> List<T>::end() noexcept
{
    Iterator<T> iterator(this->tail);
    return ++iterator;
}

template<typename T>
ConstIterator<T> List<T>::const_begin() const noexcept
{
    ConstIterator<T> iterator(this->head);
    return iterator;
}

template<typename T>
ConstIterator<T> List<T>::const_end() const noexcept
{
    ConstIterator<T> iterator(this->tail);
    if (size > 0)
        return ++iterator;
    else
        return iterator;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &list)
{
    os << "[";
    for (auto data: list)
        os << data << ", ";
    if (!list.is_empty())
        os << "\b\b" << "] ";
    else
        os << "]";
    return os;
}

template<typename T>
bool List<T>::operator==(const List<T> &list) const noexcept
{
    if (size != list.size)
        return false;
    auto iterator_in = list.const_begin();
    for (auto iterator = this->const_begin(); iterator != this->const_end(); iterator.next()) {
        if (iterator.operator->() != iterator_in.operator->())
            return false;
        ++iterator_in;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T> &list) const noexcept
{
    return not(list.head == this->head and list.tail == this->tail and this->size == list.size);
}


template<typename T>
T List<T>::pop()
{
    if (is_empty())
        throw EmptyError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    T data = head.get()->get_value();
    if (size == 1) {
        tail = nullptr;
        head = nullptr;
    } else
        head = head->get_next();
    size--;
    return data;
}


template<typename T>
List<T> List<T>::operator+(const List<T> &r_list)
{
    auto temp_list = List<T>(*this);
    temp_list.add(r_list);
    return temp_list;
}

template<typename T>
List<T> List<T>::operator+(const T &data)
{
    List<T> list(*this);
    list.add(data);
    return list;
}

template<typename T>
List<T> &List<T>::operator+=(const List<T> &list)
{
    for (auto iterator = list.const_begin(); iterator != list.const_end(); iterator.next())
        add(iterator.operator->());
    return *this;
}

template<typename T>
List<T> &List<T>::operator+=(const T &data)
{
    add(data);
    return *this;
}

template<typename T>
List<T> &List<T>::operator=(List<T> &&list) noexcept
{
    clear();
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
    list.tail = nullptr;
    list.head = nullptr;
    list.size = 0;
    return *this;
}

template<typename T>
List<T> &List<T>::operator=(const List<T> &list) noexcept
{
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
    return *this;
}

template<typename T>
Iterator<T> List<T>::add(const List<T> &list)
{
    auto result_iterator = begin();
    for (auto data: list)
        result_iterator = add(data);
    return result_iterator;
}

template<typename T>
Iterator<T> List<T>::add(T *const arr, const int &arr_size)
{
    if (!arr)
        throw PointerError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    auto iterator = nullptr;
    for (int i = 0; i < arr_size; ++i)
        iterator = add(*(arr + i));
    return iterator;
}

//template<typename T>
//List<T> &List<T>::combine(const List<T> &r_list) const
//{
//    List<T> list(*this);
//    for (auto node: r_list)
//        list.add(node);
//    return *list;
//}

template<typename T>
T List<T>::pop(Iterator<T> &in_iterator)
{
    T data = *in_iterator;
    auto next_node = (Iterator<T>(in_iterator)).get_node().get_next();
    for (auto iterator = this->begin(); iterator != this->end(); iterator++) {
        if (iterator + 1 == in_iterator) {
            iterator.get_node().set_next(next_node);
            break;
        }
    }
    return data;
}

template<typename T>
bool List<T>::is_empty() const noexcept
{
    return size == 0;
}


template<typename T>
template<class Iter>
Iterator<T> List<T>::insert(Iter &iterator, const T &data)
{
    Iterator<T> my_iterator = check_iterator(iterator);
    auto node = create_shared_from_data(data);
    node.get()->set_next(my_iterator.get_node().get_next());
    my_iterator.get_node().set_next(node);
//    node.get_node()->set_next(iterator.get_node().get_next_node());
//    iterator.get_node().set_next(node);
    return ++my_iterator;
}

template<typename T>
template<class Iter>
Iterator<T> List<T>::insert(Iter &iterator, const List<T> &list)
{
    auto list_iterator = list.const_begin();
    auto old_next_node = iterator.get_value().get_next_node();
    auto prev_node = create_shared_from_data(list_iterator.operator->());
    iterator.get_value().set_next(prev_node);
    for (list_iterator++; list_iterator != list.const_end(); list_iterator++) {
        auto node = create_shared_from_data(list_iterator.operator->());
        prev_node->set_next(node);
        prev_node = node;
    }
    prev_node->set_next(old_next_node);
    return Iterator<T>(prev_node);
}

template<typename T>
std::shared_ptr<Node<T>> List<T>::create_shared_from_data(const T &data)
{
    std::shared_ptr<Node<T>> node = nullptr;
    try {
        return std::shared_ptr<Node<T>>(new Node<T>(data));
    } catch (std::bad_alloc &e) {
        throw MemoryError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    }
}

template<typename T>
template<class Iter>
Iterator<T> List<T>::check_iterator(Iter &in_iterator)
{
    for (auto iterator = this->begin(); iterator != this->end(); iterator++)
        if (iterator == in_iterator)
            return iterator;
    throw IteratorError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
}

//template<typename T>
//Iterator<T> List<T>::insert(ConstIterator<T> &iterator, const T &data)
//{
//    auto node = create_shared_from_data(data);
//    auto prev_iterator = check_iterator(iterator);
//    node.get_node()->set_next(prev_iterator.get_value().get_next_node());
//    prev_iterator.get_value().set_next(node);
//    return ++prev_iterator;
//}

//template<typename T>
//Iterator<T> List<T>::check_iterator(ConstIterator<T> &in_iterator)
//{
//    for (auto iterator = this->begin(); iterator != this->end(); iterator++)
//        if (iterator.get_next_node_ptr() == in_iterator.get_node_ptr())
//            return iterator;
//    throw IteratorError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
//}

//template<typename T>
//Iterator<T> List<T>::insert(ConstIterator<T> &iterator, const List<T> &list)
//{
//    auto list_iterator = list.const_begin();
//    auto old_next_node = iterator.get_value().get_next_node();
//    auto prev_node = create_shared_from_data(list_iterator.operator->());
//    iterator.get_value().set_next(prev_node);
//    for (list_iterator++; list_iterator != list.const_end(); list_iterator++) {
//        auto node = create_shared_from_data(list_iterator.operator->());
//        prev_node->set_next(node);
//        prev_node = node;
//    }
//    prev_node->set_next(old_next_node);
//    return Iterator<T>(prev_node);
//}

template<typename T>
List<T>::List(List<T> &&list) noexcept
{
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
    list.size = 0;
    list.head = nullptr;
    list.tail = nullptr;
}

template<typename T>
Iterator<T> List<T>::push(const std::shared_ptr<Node<T>> &node_ptr)
{
//    std::shared_ptr<Node<T>> new_ptr;
    if (!node_ptr)
        throw PointerError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
//    new_ptr = create_shared_from_data(node_ptr->get_value());
    if (*this) {
        node_ptr.get()->set_next(this->head);
        this->head = node_ptr;
    } else {
        this->head = node_ptr;
        this->tail = node_ptr;
    }
    this->size++;
    Iterator<T> iterator(node_ptr);
    return iterator;
}

template<typename T>
Iterator<T> List<T>::push(const T &data)
{
    auto node = create_shared_from_data(data);
    return push(node);
}

template<typename T>
Iterator<T> List<T>::push(const List<T> &list)
{
    auto result_iterator = nullptr;
    for (auto node: list)
        result_iterator = push(node);
    return result_iterator;
}

template<typename T>
Iterator<T> List<T>::push(T *const arr, const int &arr_size)
{
    for (int i = arr_size; i >= 0; --i)
        push(*(arr + i));
}



template<typename T>
ConstIterator<T> List<T>::begin() const noexcept
{
    return const_begin();
}

template<typename T>
ConstIterator<T> List<T>::end() const noexcept
{
    return const_end();
}

template<typename T>
template<class Iter>
Iterator<T> List<T>::add(Iter from, Iter &to)
{
    for (;from != to; from++)
        add(*from);
    return add(*from);
}

template<typename T>
template<class Iter>
Iterator<T> List<T>::insert(Iter &iterator, Iter from, Iter &to)
{
    for (;from != to; from++)
        iterator = insert(iterator, *from);
    return add(*from);
}

template<typename T>
template<class Iter>
void List<T>::remove(Iter from, Iter to)
{
    to++;
    Iterator<T> copy = Iterator<T>(from);
    while (from != to) {
        ++copy;
        remove(from);
        from = copy;
    }

}

template<typename T>
template<class Iter>
void List<T>::remove(Iter from)
{
    if (is_empty())
        throw EmptyError(__FILE__, typeid(this).name(), __FUNCTION__, __LINE__);
    if (size == 1) {
        tail = nullptr;
        head = nullptr;
    } else
        head = head->get_next();
    size--;
}
