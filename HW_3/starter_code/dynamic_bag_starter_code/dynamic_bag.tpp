#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
  bagSize = 0;
}

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){

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
  /*
  for (int i=0;i<bagSize;i++) {
    items[i] = 
  }
  */
  return *this;
}

template<typename T>
bool DynamicBag<T>::add(const T& item) {
  T *temp = items; // Create a new pointer to the old list of items
  items = new T [bagSize+1]; // Create a new items pointer with the incremented bag size

  int n = getFrequencyOf(item); //Count the current number of occurances for comparison later

  for (int i=0;i<bagSize;i++) { // Transfer over the old temp items to the new items pointer address
      items[i] = temp[i];
  }
  items[bagSize] = item; // Add in the new items to the items pointer

  delete [] temp; // Delete the old temp items pointer
  temp = nullptr; // Cap the old temp items pointer
  bagSize++; // Increment the bag size

  return (getFrequencyOf(item) == n+1);
}

template<typename T>
bool DynamicBag<T>::remove(const T& item) {
  T *temp = items; // Create a new pointer to the old list of items
  items = new T [bagSize-1]; // Create a new items pointer with the incremented bag size

  int n = getFrequencyOf(item); //Count the current number of occurances for comparison later

  for (int i=0;i<bagSize;i++) { // Transfer over the old temp items to the new items pointer address
    if (temp[i] == item)
      items[i] = temp[i];
  }
  items[bagSize] = item; // Add in the new items to the items pointer

  delete [] temp; // Delete the old temp items pointer
  temp = nullptr; // Cap the old temp items pointer
  bagSize++; // Increment the bag size

  return !contains(entry);
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
}

template<typename T>
void DynamicBag<T>::clear(){
  //set all items to 0
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const {
  int n = 0;
    for (int i=0;i<bagSize;i++) {
        if (items[i] == entry) n++;
    }
  return n;
};
