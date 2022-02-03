/**
 * @file limited_size_bag.hpp
 * @author Hayden Feddock
 * @brief LimitedSizeBag class header file
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef LIMITED_SIZE_BAG_HPP
#define LIMITED_SIZE_BAG_HPP

#include "abstract_bag.hpp"

template <typename T>
class LimitedSizeBag: public AbstractBag<T>
{
public:
  // default constructor
  LimitedSizeBag();
  
  // copy constructor
  LimitedSizeBag(const LimitedSizeBag& x);
    
  // destructor
  ~LimitedSizeBag();
  
  // copy assignment
  LimitedSizeBag& operator=(LimitedSizeBag& x);

  // add an item to the bag
  bool add(const T & item);
  
  // remove an item
  bool remove(const T & item);

  // check is the bag is empty
  bool isEmpty() const;

  // get number of items in the bag
  std::size_t getCurrentSize() const;

  // clear the bag contents
  void clear();

  // count how many time item occurs in bag
  std::size_t getFrequencyOf(const T & item) const;

  // check if item is in the bag
  bool contains(const T& item) const;

  static const std::size_t MAXSIZE = 100;

private:
  std::size_t size;
  T items[MAXSIZE];
};

#include "limited_size_bag.tpp"

#endif
