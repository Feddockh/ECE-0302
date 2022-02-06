/**
 * @file dynamic_bag.tpp
 * @author Hayden Feddock
 * @brief 
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
  bagSize = 0;
}

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){
  bagSize = x.getCurrentSize();
  items = new T [bagSize];
  for (int i=0;i<bagSize;i++) {
    items[i] = x.items[i];
  }
}

template<typename T>
DynamicBag<T>::~DynamicBag(){
  delete [] items;
  items = nullptr;
  bagSize = 0;
}

template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T>& x) {
  bagSize = x.getCurrentSize();
  items = new T [bagSize];
  for (int i=0;i<bagSize;i++) {
    items[i] = x.items[i];
  }
  return *this;
}

template<typename T>
bool DynamicBag<T>::add(const T& item) {
  int n = getFrequencyOf(item); // Count the current number of occurances for comparison later

  T *temp = items; // Create a new pointer to the old list of items
  items = nullptr; // Was this the answer?????????????????????????????????????????????????????????????!!!!!!!!!!
  items = new T [bagSize+1]; // Create a new items pointer with the incremented bag size

  for (int i=0;i<bagSize;i++) { // Transfer over the old temp items to the new items pointer address
      items[i] = temp[i];
  }
  items[bagSize] = item; // Add in the new items to the items pointer
  bagSize++; // Increment the bag size

  delete [] temp; // Delete the old temp items pointer
  temp = nullptr; // Cap the old temp items pointer

  return (getFrequencyOf(item) == n+1); // Return true if an instance of item was added
}

template<typename T>
bool DynamicBag<T>::remove(const T& item) {
  int n = getFrequencyOf(item); // Count the current number of occurances for comparison later
  if (n == 0) return false; // This will instantly return false if there are no occurances

  bagSize--; // Decrease the bag size
  T *temp = items; // Create a new pointer to the old list of items
  items = nullptr; // Was this the answer?????????????????????????????????????????????????????????????!!!!!!!!!!
  items = new T [bagSize]; // Create a new items pointer with the incremented bag size
  
  for (int i=0,skip=0;i<bagSize;i++) { // Transfer over the old temp items to the new items pointer address
    if (temp[i] == item) skip = 1; // If the item matches an object in the old temp items pointer, set skip to 1
    items[i] = temp[i+skip]; // Use the skip to offset the values being read from the temp pointer
  }

  delete [] temp; // Delete the old temp items pointer
  temp = nullptr; // Cap the old temp items pointer

  return (getFrequencyOf(item) == n-1); // Return true if an instance of item was removed
}

template<typename T>
bool DynamicBag<T>::isEmpty() const {
  return (bagSize==0);
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const {
  return bagSize;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const {
  for (int i=0;i<bagSize;i++) {
    if (items[i] == item) return true;
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){
  bagSize = 0;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const {
  int n = 0;
    for (int i=0;i<bagSize;i++) {
        if (items[i] == item) n++;
    }
  return n;
};