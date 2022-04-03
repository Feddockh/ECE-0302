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
  return itemCount == 0;
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
          } // end if
    } // end if
    else { isValid = true; }
      
      if (canInsert) {
        //new node with entry
          Node<T>* newNodePtr = new Node<T>(item);
        //Link new node to list
          if (position == 1) {
                //put node at beginning of the chain is position is 1
                newNodePtr -> setNext(headPtr);
                headPtr = newNodePtr;
              }
          else {
                //put node after the node at position - 1
                newNodePtr -> setNext( prevPtr -> getNext() );
                prevPtr -> setNext( newNodePtr );
              } //end if
        //increment count
          itemCount++;
        } 
        else {
            throw(std::range_error("error in range"));
          } //end if
          return canInsert; 
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  return T();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
