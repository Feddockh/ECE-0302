#include "deque.hpp"

template <typename T>
bool Deque<T>::isEmpty() const noexcept {
    return list.isEmpty();
}

template <typename T>
void Deque<T>::pushFront(const T & item) {
    if (!list.insert(1, item)) 
        throw(std::bad_alloc());
}

template <typename T>
void Deque<T>::popFront() {
    if (list.isEmpty()) 
        throw(std::runtime_error("Cannot pop from an empty list"));
    if (!list.remove(1))
        throw(std::runtime_error("Linked list error"));
}

template <typename T>
T Deque<T>::front() const {
    if (list.isEmpty()) 
        throw(std::runtime_error("Cannot peek from an empty list"));
    return list.getEntry(1);
}

template <typename T>
void Deque<T>::pushBack(const T & item) {
    if (!list.insert(list.getLength() + 1, item)) // length + 1 because we are adding past the last item
        throw(std::bad_alloc());
}

template <typename T>
void Deque<T>::popBack() {
    if (list.isEmpty()) 
        throw(std::runtime_error("Cannot pop from an empty list"));
    if (!list.remove(list.getLength()))
        throw(std::runtime_error("Linked list error"));
}

template <typename T>
T Deque<T>::back() const {
    if (list.isEmpty()) 
        throw(std::runtime_error("Cannot peek from an empty list"));
    return list.getEntry(list.getLength());
}