/**
 * @file array_list.tpp
 * @author Hayden Feddock
 * @brief Methods for the array list
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "array_list.hpp"

// constructor
template <typename T>
ArrayList<T>::ArrayList() {
  size = 0;
  list = new T;
}

// destructor
template <typename T>
ArrayList<T>::~ArrayList() {
  size = 0;
  delete [] list;
  list = nullptr;
}

// copy constructor because a new address for list is needed
template <typename T>
ArrayList<T>::ArrayList(const ArrayList & rhs){
  size = rhs.size;
  list = new T[size];
  for (int i=0;i<size;i++) {
    list[i] = rhs.list[i];
  }
}

// equals operator because a new address for list is needed
template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList & rhs){
  delete [] list;
  list = nullptr;

  size = rhs.size;
  list = new T[size];
  for (int i=0;i<size;i++) {
    list[i] = rhs.list[i];
  }
  return *this;
}

// returns true if empty
template <typename T>
bool ArrayList<T>::isEmpty() const{ 
  return (size==0);
}

// returns the length
template <typename T>
std::size_t ArrayList<T>::getLength() const{
  return size;
}

/*
* stores the old list address to a temporary pointer and creates another list with the new size
* stores the values from the old list into the new list up to the position specified
* at the specified position, the inserted item outside of the for loop
* the rest of the old list is copied over using another for loop
* the pointer to the old list is deleted
*/
template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  if (position > size+1 || position < 1) return false;
  
  T *temp = list;
  size++;
  list = new T[size];

  int i=0;
  for (i;i<position-1;i++) {
    list[i] = temp[i];
  }
  list[i++] = item;
  for (i;i<size;i++) {
    list[i] = temp[i-1];
  }

  delete [] temp;
  temp = nullptr;

  return true;
}

/*
* stores the old list address to a temporary pointer and creates another list with the new size
* stores the values from the old list into the new list up to the position specified
* at the specified position, the next loop is entered
* This new loop offsets the index used with the old list to skip past the item at the position
* the pointer to the old list is deleted
*/
template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  if (position > size || position < 1 || size == 0) return false;

  T *temp = list;
  size--;
  list = new T[size];

  int i=0;
  for (i;i<position-1;i++) {
    list[i] = temp[i];
  }
  for (i;i<size;i++) {
    list[i] = temp[i+1];
  }

  delete [] temp;
  temp = nullptr;

  return true;
}

// sets size to zero, does not deallocate memory (no need)
template <typename T>
void ArrayList<T>::clear() {
  size = 0;
}

// retrieves a value from the list
template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  return list[position-1];
}

// sets a value in the list
template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  list[position-1] = newValue;
}
