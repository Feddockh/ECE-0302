#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() {
  size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  //TODO
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  //TODO
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  //TODO
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //TODO
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
  return (size==0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const {
  return size;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item) {
  if (position > size+1 || position < 1) return false;

  size++;
  if (size==1) {
    list = new Node<T>;
    list->setItem(item); 
    return true;
  }

  Node<T> *leftNode = list, *rightNode;

  for (int i=0;i<position-2;i++) {
    leftNode = leftNode->getNext();
  }

  Node<T> *newNode = new Node<T>;
  newNode->setItem(item);
  if (position<size) rightNode = leftNode->getNext();

  leftNode->setNext(newNode);
  if (position<size) newNode->setNext(rightNode);

  leftNode = nullptr;
  rightNode = nullptr;

  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position) {
  if (position > size || position < 1 || size == 0) return false;
  size--;

  Node<T> *leftNode = list, *oldNode, *rightNode;

  for (int i=0;i<position-2;i++) {
    leftNode = leftNode->getNext();
  }

  oldNode = leftNode->getNext();
  if (position<size) rightNode = oldNode->getNext();

  if (position<size) leftNode->setNext(rightNode);

  delete [] oldNode;
  oldNode = nullptr;
  leftNode = nullptr;
  rightNode = nullptr;

  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const {
  Node<T> *leftNode = list;

  for (int i=0;i<position-1;i++) {
    leftNode = leftNode->getNext();
  }
  
  return leftNode->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue) {

}
