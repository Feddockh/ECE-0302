#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty()
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength()
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  size_t length = LinkedList<T>::getLength();
  size_t i = 0;

  while (i < length) {
    if (getEntry(i) > item) break;
    i++;
  }

  LinkedList<T>::insert(i, item);
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");

  size_t length = LinkedList<T>::getLength();
  size_t i = 0;

  while (i < length) {
    if (getEntry(i) == item) {
      LinkedList<T>::remove(i);
      break;
    }
    i++;
  }
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty()) throw std::range_error("empty list in remove");

  LinkedList<T>::remove(position);

}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position)
{
  return LinkedList<T>::getEntry(position);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& newValue)
{
  int length = getLength();
  long int i = 0;

  // Check if there are any equal items
  while (i < length) {

    if (getEntry(i) == newValue) return i;

    i++;
  }

  // Find position where the item should be
  while (i < length) {

    if (getEntry(i) > newValue) return (i-1);

    i++;
  }

  return 0;
}
