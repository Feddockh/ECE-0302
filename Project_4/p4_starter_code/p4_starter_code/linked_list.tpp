#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() {
  itemCount = 0;
  headPtr = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x) {
  itemCount = x.itemCount;                         // Copy over the item count
  Node<T> *origPtr = x.headPtr;                    // Make a pointer to the nodes of list x

  if (origPtr == nullptr) {                        // Check whether list x pointer is empty
    headPtr = nullptr;                             // If the list x pointer is empty, set the pointer to nullptr

  } else {                                         // If not empty, copy the values from the x list over
    headPtr = new Node<T>;                         // Create a new node
    headPtr->setItem(origPtr->getItem());          // Copy over the value from the first node of list x

    Node<T> *newPtr = headPtr;                     // Create a pointer to the current head pointer
    origPtr = origPtr->getNext();                  // Slide the pointer down the list

    while (origPtr != nullptr) {
      T nextItem = origPtr->getItem();             // Pull the value of the next item from list x
      Node<T> *newNodePtr = new Node<T>(nextItem); // Create a new node with the value from list x
      newPtr->setNext(newNodePtr);                 // Set the next node to the new node with the list x value using the pointer
      
      newPtr = newPtr->getNext();                  // Slide the pointer down the list
      origPtr = origPtr->getNext();                // Slide the pointer down the list
    }
  }
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y) {
  LinkedList<T> temp(x);
  x = y;
  y = temp;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x) {
  itemCount = x.itemCount;                         // Copy over the item count
  Node<T> *origPtr = x.headPtr;                    // Make a pointer to the nodes of list x

  if (origPtr == nullptr) {                        // Check whether list x pointer is empty
    headPtr = nullptr;                             // If the list x pointer is empty, set the pointer to nullptr

  } else {                                         // If not empty, copy the values from the x list over
    headPtr = new Node<T>;                         // Create a new node
    headPtr->setItem(origPtr->getItem());          // Copy over the value from the first node of list x

    Node<T> *newPtr = headPtr;                     // Create a pointer to the current head pointer
    origPtr = origPtr->getNext();                  // Slide the pointer down the list

    while (origPtr != nullptr) {
      T nextItem = origPtr->getItem();             // Pull the value of the next item from list x
      Node<T> *newNodePtr = new Node<T>(nextItem); // Create a new node with the value from list x
      newPtr->setNext(newNodePtr);                 // Set the next node to the new node with the list x value using the pointer
      
      newPtr = newPtr->getNext();                  // Slide the pointer down the list
      origPtr = origPtr->getNext();                // Slide the pointer down the list
    }
  }

  return *this;                                    // Return the instance of the list
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
  return (itemCount == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const {
  return itemCount;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item) {
  bool canInsert = (position >= 1) && (position <= itemCount +1);
  Node<T>* prevPtr = getNodeAt(position - 1);
  
  bool isValid;
  if (position+1 <= itemCount) {
    Node<T>* postPtr = getNodeAt(position + 1);
    if (position-1 >= 1 ) {
      isValid = (prevPtr -> getItem() < item) && (postPtr -> getItem() > item); } 
    else { 
      isValid = (postPtr -> getItem()) > item; 
    }
  } else { 
    isValid = true; }
    if (canInsert) {
      //new node with entry
      Node<T>* newNodePtr = new Node<T>(item);
      //Link new node to list
      if (position == 1) {
        //put node at beginning of the chain is position is 1
        newNodePtr -> setNext(headPtr);
        headPtr = newNodePtr;
      } else {
        //put node after the node at position - 1
        newNodePtr -> setNext( prevPtr -> getNext() );
        prevPtr -> setNext( newNodePtr );
      } //end if
      //increment count
      itemCount++;
    } else {
      throw(std::range_error("error in range"));
    }
  return canInsert; 
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position) {
  bool canRemove = (position >= 1) && (position <= itemCount);
  if (canRemove) {
    Node<T>* curPtr = nullptr;
    if (position == 1) {
    //Remove first node
      curPtr = headPtr;
      headPtr = headPtr -> getNext();
    } else {
      //get node in position before one to be removed
      Node<T>* prevPtr = getNodeAt(position - 1);
      //point to node being removed
      curPtr = prevPtr -> getNext();
      //connect node before the one being removed to the position after it, unlinking the node to be removed
      prevPtr -> setNext( curPtr -> getNext() );
    }
    //set current pointer back to null
    curPtr -> setNext(nullptr);
    delete curPtr;
    curPtr = nullptr;
    //deincrement count
    itemCount--;
  } else {
    throw(std::range_error("error in range"));
  } // end if
  return canRemove;
}

template <typename T>
void LinkedList<T>::clear() {
  while (!isEmpty())
    //remove the first entry until isEmpty() returns true
    remove(1); 
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const {
  //preconditions
  bool canGet = (position >= 1) && (position <= itemCount);
  if (canGet) {
    Node<T>* nodePtr = getNodeAt(position);
    return nodePtr -> getItem();
  } else {
    throw(std::range_error("error in range"));
  } // end if
  return T();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue) {
  bool canSet = (position >= 1) && (position <= itemCount +1);
  Node<T>* prevPtr = getNodeAt(position - 1);
  
  bool isValid;
  if (position+1 <= itemCount) {
    Node<T>* postPtr = getNodeAt(position + 1);
    if (position-1 >= 1 ) {
      isValid = (prevPtr -> getItem() < newValue) && (postPtr -> getItem() > newValue); 
    } else { 
      isValid = (postPtr -> getItem()) > newValue; 
    } // end if
  } else { 
    isValid = true; 
  }
           
  if (canSet) {
    while ( itemCount >= position) {
      remove(position); 
    }
    insert(position, newValue);
  } else { 
    throw(std::range_error("error in range")); 
  } 
}

template <typename T>
Node<T>* LinkedList<T>::getNodeAt(int position) const {
  // precondition: make sure function only preforms if condition is met (should always be met
  //because getNodeAt() is private function)
  //assert((position >= 1) && (position <= itemCount));
  //count through from beginning of list to position
  
  Node<T>* curPtr = headPtr;
  for (std::size_t next = 1; next < position; next++)
    curPtr = curPtr -> getNext();
  return curPtr;
} //end getNodeAt
