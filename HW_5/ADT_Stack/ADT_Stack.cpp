/**
 * @file ADT_Stack.cpp
 * @author Hayden Feddock
 * @brief Implementation for ADT_Stack header
 * @version 0.1
 * @date 2022-02-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ADT_Stack.hpp"

// constructor
template <typename T>
ADT_Stack<T>::ADT_Stack() {
    size = 0;
    space = 10;
    items = new T[space];
    h = k = false;
    addk = 3;
}

// destructor
template <typename T>
ADT_Stack<T>::~ADT_Stack() {
    size = 0;
    delete [] items;
    items = nullptr;
}

// add and then double size when full
template<typename T>
bool ADT_Stack<T>::add(const T& item) {

    if (size+1>=space/(1+h)) { // Enter if statement when the space is full
        
        if (k && !h) {
            space = addk;
            addk += 2;
        } else {
            space *= 2; // Double the space
        }

        T *temp = items; // Create a new pointer to the old list of items
        items = nullptr; // Cap the variable
        items = new T [space]; // Create a new items pointer with the doubled size

        for (int i=0;i<size;i++) { // Transfer over the old temp items to the new items pointer address
            items[i] = temp[i];
        }

        delete [] temp; // Delete the old temp items pointer
        temp = nullptr; // Cap the old temp items pointer
    } 

    items[size] = item; // Add in the new item to the items pointer
    size++; // Increment the size

  return true;
}

template<typename T>
bool ADT_Stack<T>::remove() {

    size--; // Decrease the size

    if (size<space/2 && space>10) { // If the size is less than half of the space and the space is greater than 10
        space /= 2; // Half the space available

        T *temp = items; // Create a new pointer to the old list of items
        items = nullptr; // Cap the pointer
        items = new T [space]; // Create a new items pointer with the decremented bag size
  
        for (int i=0;i<size;i++) { // Transfer over the old temp items to the new items pointer address
            items[i] = temp[i];
        }

        delete [] temp; // Delete the old temp items pointer
        temp = nullptr; // Cap the old temp items pointer
    }

    return true;
}


