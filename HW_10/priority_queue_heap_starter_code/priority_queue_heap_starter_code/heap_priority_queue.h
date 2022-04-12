
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_

#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"

template <typename T>
class HeapPriorityQueue: public AbstractPriorityQueue<T>
{
public:
    
    // return true if the priority queue is empty
    bool isEmpty();
    
    // insert item into the queue
    void add(const T& item);
    
    // remove highest priority item from the queue
    void remove();
    
    // get the item with the highest priority from the queue
    T peek();
    
private:
    
    DynamicArrayList<T> lst;
};

template <typename T>
bool HeapPriorityQueue<T>::isEmpty() {
    return lst.getLength() == 0;
}

template <typename T>
void HeapPriorityQueue<T>::add(const T& item) {

    // Get the current node index and the parent node index
    int i = lst.getLength();
    int p = i >> 1;

    // Inserts item to the back of the queue
    lst.insert(i, item);

    // If the current node index is 0, then we just inserted the first item
    if (i == 0) return;
    
    // Check if the parent of the item is greater
    while (lst.getEntry(p) < item) {

        // If the parent is larger than the item, switch the parent and current node values
        lst.setEntry(i, lst.getEntry(p));
        lst.setEntry(p, item);

        // Move the current node index and parent node index up
        i = p;
        p = p >> 1;
    }
}

template <typename T>
void HeapPriorityQueue<T>::remove() {

    int length = lst.getLength();

    if (length == 0) return;

    if (length == 1) {
        lst.remove(0);
        return;
    }

    if (length == 2) {
        lst.setEntry(0, lst.getEntry(1));
        lst.remove(1);
        return;
    }

    /*
    // Otherwise (length > 2) move the 1st entry up to the 0th
    lst.setEntry(0, lst.getEntry(1));

    int i = 1;
    int lc, rc;

    while (true) {
        // Shift the child indicies using the current index
        lc = i << 1;
        rc = 1 + i << 1;

        // Check if there is a left child
        if (lc >= length) {
            break; // No children
        }

        // Check if there is a right child
        if (rc >= length) {
            i = lc; // Only child is left child
            break;
        }

        // If there is both a right and left child, we have to compare them
        if (lst.getEntry(lc) > lst.getEntry(rc)) {
            lst.setEntry(i, lst.getEntry(lc));
            i = lc;
        } else {
            lst.setEntry(i, lst.getEntry(rc));
            i = rc;
        }
    }

    // Once we have worked our way down to the lowest point, we can remove the node

    // EDIT
    // This remove method won't work because we may not be removing from the end and the dynamic
    // array will shift all the child nodes which will mess up our order
    */

    HeapPriorityQueue<T> temp;

    // Copy over all entries but the first one (removes highest priority)
    for (int i=1;i<length;i++) {
        temp.add(lst.getEntry(i));
    }

    // Swap the new priority queue list with the current one
    lst.swap(lst, temp.lst);
    
}

template <typename T>
T HeapPriorityQueue<T>::peek() {
    return lst.getEntry(0);
}


#endif // _HEAP_PRIORITY_QUEUE_H_
