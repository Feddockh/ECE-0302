#include "linked_list.hpp"

#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() 
{
  headptr = nullptr;
  list_length = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() 
{
  clear();  // Clears the list, deallocating memory
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  headptr = x.headptr;
  list_length = 0;
  for (int i = 1; i <= x.list_length; i++)
  {
    insert(i,x.getEntry(i));
  }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  this->clear();
  this->headptr = x.headptr;
  this->list_length = 0;
  for (int i = 1; i <= x.list_length; i++)
  {
    this->insert(i,x.getEntry(i));
  }
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if (list_length == 0)
  {
    return true;
  }
  return false;
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return list_length;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if (position < 1 || position > list_length + 1)  // If position invalid
  {
    return false;
  }
  Node<T> *newNodePtr = new Node<T>;   
  newNodePtr->setItem(item);
  Node<T> *prevNodePtr = headptr;  // Pointer to Node before obejct to be inserted
  
  if (position == 1)  // If new object is start of the chain
  {
    newNodePtr->setNext(headptr);
    headptr = newNodePtr;  // New item is head pointer
  }
  else 
  {
    for (std::size_t i = 2; i < position; i++)
    {
      prevNodePtr = prevNodePtr->getNext();  // Traverse list until we reach object before current position
    }
    if (position != list_length + 1)
    {
      newNodePtr->setNext(prevNodePtr->getNext());
    }
    prevNodePtr->setNext(newNodePtr);
  }
  list_length++;
  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  Node<T> *prevNodePtr = headptr;
  Node<T> *tempNodePtr;  // Pointer to preserve chain after deletion
  if (position < 1 || position > list_length)  // If position invalid
  {
    return false;
  }
  if (position == 1)  // If deleted object is start of the chain
  {
    prevNodePtr = prevNodePtr->getNext();
    delete headptr;
    headptr = prevNodePtr;
  }
  else
  {
    for (std::size_t i = 2; i < position; i++)
    {
      prevNodePtr = prevNodePtr->getNext();  // Traverse list until we reach object before current position
    }
    if (position != list_length)
    {
      tempNodePtr = (prevNodePtr->getNext())->getNext();
      Node<T> *deletePointer = prevNodePtr->getNext();
      deletePointer = nullptr;
      delete deletePointer;  // Deletes object
      delete prevNodePtr->getNext();
      prevNodePtr->setNext(tempNodePtr);
    }
    else
    {
      delete prevNodePtr->getNext();
    }
  }
  list_length--;
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  std::size_t n = list_length;
  for (std::size_t i = 1; i <= n; i++)
  {
    remove(1);
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  Node<T> *tempNodePtr = headptr;
  for (std::size_t i = 2; i <= position; i++)
  {
    tempNodePtr = tempNodePtr->getNext();
  }
  return tempNodePtr->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  Node<T> *tempNodePtr = headptr;
  for (std::size_t i = 2; i <= position; i++)
  {
    tempNodePtr = tempNodePtr->getNext();
  }
  tempNodePtr->setItem(newValue);
}
