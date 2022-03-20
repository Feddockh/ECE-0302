#include "dynamic_array_list.h"

#include <algorithm>
#include <stdexcept>

#include <iostream>

template <typename T>
DynamicArrayList<T>::DynamicArrayList() {
  size = 0;
  capacity = 10;
  data = new T[capacity];
}

template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T>& x) {
  capacity = x.capacity;
  size = x.size;

  data = new T[capacity];    // Create an array with list x capacity
  for (int i=0;i<size;i++) { // Increment through array and copy items over
    data[i] = x.data[i];
  }
}

template <typename T>
DynamicArrayList<T>::~DynamicArrayList() {
  std::clog << "DynamicArrayList Destructor called." << std::endl;
  capacity = 0;
  size = 0;
  delete [] data;
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x) {
  capacity = x.capacity;
  size = x.size;

  T *temp = data;            // Set a temporary pointer to data
  data = new T[capacity];    // Recreate data with the new capacity
  delete [] temp;            // Delete the temporary array and cap with nullptr
  temp = nullptr;

  for (int i=0;i<size;i++) { // Increment through array and copy items over
    data[i] = x.data[i];
  }
  return *this;              // Return the object
}

template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& y) {
  T *temp = data;
  data = y;
  y = temp;
  temp = nullptr;
}

template <typename T>
bool DynamicArrayList<T>::isEmpty() {
  return size == 0;
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength() {
  return size;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item) {
  if (position < 0) throw std::range_error("invalid position"); // Check that position is valid and above 0
  if (position > size) throw std::range_error("invalid position"); // Check that position is valid and smaller or equal to size
  
  if (size+1 >= capacity) capacity += 10; // Increment capacity if at max

  T *temp = data;
  data = new T[capacity];                 // Create a new data array with the current capacity

  int i = 0;
  for (i;i<position;i++) {                // Increment through array and copy items over up to position
    data[i] = temp[i];
  }
  data[i] = item;                         // At position, add in the new item
  for (i;i<size;i++) {                    // Increment through remaining array and copy items over
    data[i+1] = temp[i];
  }

  size++;                                 // Increment size

  delete [] temp;                         // Delete the temp array and cap
  temp = nullptr;
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position) {
  if (size == 0) throw std::range_error("empty stack"); // Check that the stack is not empty
  if (position < 0) throw std::range_error("invalid position"); // Check that position is valid
  if (position >= size) throw std::range_error("invalid position"); // Check that position is valid

  if (size-1 <= capacity-10) capacity -= 10; // Decrement capacity if 10 less than capacity
  size--;                                    // Decrement size

  T *temp = data;
  data = new T[capacity];                 // Create a new data array with the current capacity

  int i = 0;
  for (i;i<position;i++) {                // Increment through array and copy items over up to position
    data[i] = temp[i];
  }
  for (i;i<size;i++) {                    // Increment through remaining array after skipping over position
    data[i] = temp[i+1];
  }

  delete [] temp;                         // Delete the temp array and cap
  temp = nullptr;
}

template <typename T>
void DynamicArrayList<T>::clear() {
  while (size > 0) remove(0); // Remove until size is 0
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position) {
  if (size == 0) throw std::range_error("empty stack"); // Check that the stack is not empty
  if (position < 0) throw std::range_error("invalid position"); // Check that position is valid
  if (position >= size) throw std::range_error("invalid position"); // Check that position is valid
  return data[position];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if (position < 0) throw std::range_error("invalid position"); // Check that position is valid
  if (position >= size) throw std::range_error("invalid position"); // Check that position is valid
  data[position] = newValue;
}
