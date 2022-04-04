#include "deque.hpp"

template <typename T>
bool Deque<T>::isEmpty() const noexcept {
    return list.isEmpty();
}

template <typename T>
void Deque<T>::pushFront(const T & item) {
    // How should I use: throw(std::bad_alloc("Allocation Error"));
    list.insert(0, item);
}

template <typename T>
void Deque<T>::popFront() {
    if (list.isEmpty()) throw(std::runtime_error("Cannot pop from an empty list"));
    list.remove(0);
}

template <typename T>
T Deque<T>::front() const {
    if (list.isEmpty()) throw(std::runtime_error("Cannot peek from an empty list"));
    return list.getEntry(0);
}

template <typename T>
void Deque<T>::pushBack(const T & item) {
    // How should I use: throw(std::bad_alloc("Allocation Error"));
    list.insert(list.getLength(), item);
}

template <typename T>
void Deque<T>::popBack() {
    if (list.isEmpty()) throw(std::runtime_error("Cannot pop from an empty list"));
    list.remove(list.getLength());
}

template <typename T>
T Deque<T>::back() const {
    if (list.isEmpty()) throw(std::runtime_error("Cannot peek from an empty list"));
    return list.getEntry(list.getLength()); // TODO: Might have to be length-1
}