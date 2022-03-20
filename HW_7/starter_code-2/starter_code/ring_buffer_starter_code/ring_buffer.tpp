#include "ring_buffer.h"

#include <cassert>

template <typename T>
RingBuffer<T>::RingBuffer(std::size_t size)
{
  queueLength = size;
  data.reset(new T[queueLength]);
  front = 0;
  back = queueLength-1;
  count = 0;
}

template <typename T> 
bool RingBuffer<T>::enqueue_front(const T& item) {
  if(count != queueLength) {
    front -= 1;                          // Subtract 1 from the front so that the cursor goes right
    if (front < 0) front += queueLength; // If the cursor goes beyond zero have it wrap back around
    data[front] = item;                  // Store the item at the cursor
    ++count;
    return true;
  }

  return false;
}

template <typename T>
bool RingBuffer<T>::enqueue_back(const T& item) {
  if(count != queueLength) {
    back = (back + 1) % queueLength;
    data[back] = item;
    ++count;
    return true;
  }
  
  return false;
}

template <typename T>
T RingBuffer<T>::dequeue_front() {
  assert(count > 0);
  
  T value;
  
  value = data[front];
  front = (front + 1) % queueLength;
  --count;
  
  return value;
}


template <typename T> 
T RingBuffer<T>::dequeue_back() {
  assert(count > 0);
  
  T value;
  
  value = data[back];
  back -= 1;                          // Subtract 1 from the back so that the cursor goes right
  if (back < 0) back += queueLength; // If the cursor goes beyond zero have it wrap back around
  --count;
  
  return value;
}


template <typename T>
long int RingBuffer<T>::getCount()
{
  return count;
}
