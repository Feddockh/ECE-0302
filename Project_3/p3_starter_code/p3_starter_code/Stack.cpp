//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

template<class ItemType>
Stack<ItemType>::Stack() {
	currentSize = 0;
    headPtr = nullptr;
}

template<class ItemType>
Stack<ItemType>::~Stack() {
	clear();
}

template<class ItemType>
bool Stack<ItemType>::isEmpty() const {
	return currentSize == 0;
}

template<class ItemType>
int Stack<ItemType>::size() const {
	return currentSize;
}

template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem) {

	// Creare a new node with the new item and the address of the chain of nodes
	Node<ItemType>* nextNodePtr = new Node<ItemType>(newItem, headPtr);

	headPtr = nextNodePtr; // Set the new node to be the head node
	currentSize++;         // Increment the size

	return true;           // The method is always successful
}

template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error) {
	if (currentSize == 0) return NULL; // Return null if the stack is empty (TODO: check this later)
	return headPtr->getItem();         // If the stack is not empty then return the item
}

template<class ItemType>
bool Stack<ItemType>::pop() {

	if (currentSize == 0) return false; // Return false if the size is already zero

	Node<ItemType> *temp = headPtr;     // Create a temporary pointer to delete later

	if (currentSize==1) {               // Set the headPtr to the next pointer of it's node
		headPtr = nullptr;
	} else {
		headPtr = headPtr->getNext();
	}

	delete temp;                        // Delete the node stored in the temp pointer
	temp = nullptr;                     // Cap the temp pointer
	currentSize--;                      // Decrement the size

	return true;
}

template<class ItemType>
void Stack<ItemType>::clear() {
	while (pop() == true); // Continue popping until the function returns false (size is zero)
}