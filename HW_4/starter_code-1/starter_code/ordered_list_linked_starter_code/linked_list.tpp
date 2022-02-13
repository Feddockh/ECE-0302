/**
 * @file linked_list.tpp
 * @author Hayden Feddock
 * @brief methods for the linked list
 * @version 0.1
 * @date 2022-02-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "linked_list.hpp"

// the only thing we need to do for the constructor is set the size to zero
template <typename T>
LinkedList<T>::LinkedList() {
  size = 0;
}

// the destructor uses the clear function to destroy every node
template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

/* 
* initializes the size, copies the list pointer from object x
* travels down the object x list while inserting the items from each node into the new list
* caps the pointer used to traverse the object x list
*/
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x) {
  size = 0;
  Node<T> *xNode = x.list;
  for (int i=1;i<=x.size;i++) {
    if (i>1) xNode = xNode->getNext();
    insert(i, xNode->getItem());
  }
  xNode = nullptr;
}

/*
* copies the pointer to the first node and the list size from object x
* stores the pointer to the first node and the list size of object y to object x
* stores the pointer to the first node and the list size of the object x copy to object y
*/
template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y) {
  size_t tempSize = x.size;
  Node<T> *tempList = x.list;

  x.size = y.size;
  x.list = y.list;

  y.size = tempSize;
  y.list = tempList;
}

/*
* uses the clear function to delete all existing node and reset the list size
* copies the list pointer from object x which will be used to traverse the list
* travels down the object x list while inserting the items from each node into the new list
* caps the pointer used to traverse the object x list
* returns an instance of the object
*/
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x) {
  clear();
  Node<T> *xNode = x.list;
  for (int i=1;i<=x.size;i++) {
    if (i>1) xNode = xNode->getNext();
    insert(i, xNode->getItem());
  }
  xNode = nullptr;
  return *this;
}

// returns true if the size is 0
template <typename T>
bool LinkedList<T>::isEmpty() const {
  return (size==0);
}

// returns the size of the list
template <typename T>
std::size_t LinkedList<T>::getLength() const {
  return size;
}

/*
* checks to make sure that the given position is compatable with the list size
* increments the list size
* if the list was empty, then it just makes a node, sets it, and assigns it to the list pointer
* if the list wasn't empty, then a left node and right node pointer are made
* the left node pointer traverses the list until just before the desired position of the new node
* a new node is made, and it is set with the item
* if we are inserting at the beginning of the list, then we change the list pointer to the new node
* we also take the address of the previous first node and set it to the next address of the new node
* if the position is not 1, then it has to determine whether we are inserting to the middle or end
* if we are inserting on the end, then we can just store the address of the new node to the last node
* otherwise, we find the right node, store it to the next pointer of the new node, and set the left node
* cap the pointers to the left and right nodes
*/
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

  for (int i=2;i<position;i++) {
    leftNode = leftNode->getNext();
  }

  Node<T> *newNode = new Node<T>;
  newNode->setItem(item);

  if (position==1) {
    rightNode = list;
    newNode->setNext(rightNode);
    list = newNode;
  } else {
    if (position<size) {
      rightNode = leftNode->getNext();
      newNode->setNext(rightNode);
    }
    leftNode->setNext(newNode);
  }

  leftNode = nullptr;
  rightNode = nullptr;

  return true;
}

/*
* checks to make sure that the given position is compatable with the list size
* decrements the list size
* a left node, right node, and old node pointer are made
* the left node pointer traverses the list until just before the node to be removed
* if the node is at position 1, then the old node pointer is set
* and if the size of the list is greater than 1, then the right node is stored to the list pointer
* if the position is not first, but is at the end of the list, then just the old node pointer set
* otherwise, we find the old node, then find the right node and store it to the pointer of the left node
* now we safely delete the old node
* cap the pointers to the left and right nodes
*/
template <typename T>
bool LinkedList<T>::remove(std::size_t position) {
  if (position > size || position < 1 || size == 0) return false;
  
  size--;

  Node<T> *leftNode = list, *oldNode, *rightNode;

  for (int i=2;i<position;i++) {
    leftNode = leftNode->getNext();
  }

  if (position==1) {
    oldNode = leftNode;
    if (position<=size) {
      rightNode = oldNode->getNext();
      list = rightNode;
    }
  } else {
    oldNode = leftNode->getNext();
    if (position<=size) {
      rightNode = oldNode->getNext();
      leftNode->setNext(rightNode);
    }
  }

  delete [] oldNode;
  oldNode = nullptr;
  leftNode = nullptr;
  rightNode = nullptr;

  return true;
}


// uses the remove function to delete each node of the list from back to front
template <typename T>
void LinkedList<T>::clear() {
  for (int i=size;i>=1;i--)
    remove(i);
  list = nullptr;
}

// creates a pointer to traverse the list up to the target node, then gets the node item
template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const {
  Node<T> *targetNode = list;
  for (int i=1;i<position;i++) {
    targetNode = targetNode->getNext();
  }
  return targetNode->getItem();
}

// creates a pointer to traverse the list up to the target node, then sets node item
template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue) {
  Node<T> *targetNode = list;
  for (int i=1;i<position;i++) {
    targetNode = targetNode->getNext();
  }
  targetNode->setItem(newValue);
}
