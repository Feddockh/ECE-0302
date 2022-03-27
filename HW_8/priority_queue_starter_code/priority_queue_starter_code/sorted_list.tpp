#include "sorted_list.h"

template <typename T, typename L>
SortedList<T, L>::SortedList()
{
  // nothing to do, plist gets created on the stack
}

template <typename T, typename L>
SortedList<T, L>::SortedList(const SortedList<T, L> & x)
{
  plist = x.plist; // use copy assignment to implement copy construction
}

template <typename T, typename L>
SortedList<T, L>& SortedList<T, L>::operator=(const SortedList<T, L>& x)
{
  plist = x.plist;
  return *this;
}

template <typename T, typename L>
SortedList<T, L>::~SortedList()
{
  // plist destructor gets called automatically
}

template <typename T, typename L>
bool SortedList<T, L>::isEmpty()
{
  return plist.isEmpty();
}

template <typename T, typename L>
std::size_t SortedList<T, L>::getLength()
{
  return plist.getLength();
}

template <typename T, typename L>
void SortedList<T, L>::insert(const T& item)
{
  // TODO
  L tempList;                                // Create a temporary list

  tempList.swap(plist);                      // Move all the items from the plist to the temporary one

  int i = 0;                                 // Set increment variable
  int length = tempList.getLength();         // Get the length

  while(i<length) {                          // Use a loop to transfer all values less than item back into plist
    if (tempList.getEntry(i) > item) break;
    plist.insert(i, tempList.getEntry(i));
    i++;
  }
  plist.insert(i++,item);                    // Add the item into plist at the sorted position and increment i
  while(i<length+1) {                        // Continue to transfer all remaining items back into plist
    plist.insert(i, tempList.getEntry(i-1));
    i++;
  }
}

template <typename T, typename L>
void SortedList<T, L>::remove(const T& item)
{
  // TODO
  int i = 0;                         // Set increment variable
  int length = plist.getLength();    // Get the length

  while(i<length) {                  // Loop until first occurance of item, then remove it and break loop
    if (plist.getEntry(i) == item) {
      plist.remove(i);
      break;
    }
    i++;
  }
}

template <typename T, typename L>
void SortedList<T, L>::removeAt(std::size_t position)
{
  plist.remove(position);
}

template <typename T, typename L>
void SortedList<T, L>::clear()
{
  plist.clear();
}

template <typename T, typename L>
T SortedList<T, L>::getEntry(std::size_t position)
{
  return plist.getEntry(position);
}

template <typename T, typename L>
long int SortedList<T, L>::getPosition(const T& newValue)
{
  // TODO
  int length = plist.getLength();                // Get the length

  int i = 0;                                     // Set increment variable
  while (i < length) {                           // Check if there are any equal items
    if (plist.getEntry(i) == newValue) return i; // Return position
    i++;
  }

  i = 0;                                         // Reset increment variable
  while (i < length) {                           // Find position where the item should be
    if (plist.getEntry(i) > newValue) return -i; // Return negated position
    i++;
  }

  return -i-1; // Return a negated position at the very end of the list if the value didn't fit elsewhere
}
