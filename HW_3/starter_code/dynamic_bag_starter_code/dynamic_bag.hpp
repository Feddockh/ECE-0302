/**
 * @file dynamic_bag.hpp
 * @author Hayden Feddock
 * @brief DynamicBag class header file
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define _DYNAMIC_BAG_HPP_

#include "abstract_bag.hpp"

template <typename T>
class DynamicBag: public AbstractBag<T> {
  private:
    T *items;
    int bagSize;
    
  public:
    // default constructor
    DynamicBag();

    // copy constructor
    DynamicBag(const DynamicBag& x);
      
    // destructor
    ~DynamicBag();

    // copy assignment
    DynamicBag& operator=(DynamicBag& x);

    // add an item to the bag
    bool add(const T & item);

    // remove an item
    bool remove(const T & item);

    // check if the bag is empty
    bool isEmpty() const;

    // get number of items in the bag
    std::size_t getCurrentSize() const;

    // clear the bag contents
    void clear();

    // count how many time item occurs in bag
    std::size_t getFrequencyOf(const T & item) const;

    // check if item is in the bag
    bool contains(const T& item) const;
};

#include "dynamic_bag.tpp"

#endif
