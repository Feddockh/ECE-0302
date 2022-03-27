#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"

TEST_CASE("Testing Sorted List", "[sorted list]") {
  typedef SortedList<int, DynamicArrayList<int> > slst;
  // TODO

  slst testList;
  int max = 20;

  for (int i=max;i>0;i--) { // Insert values from 20 -> 1
    testList.insert(i);
  }
  for (int i=0;i<max;i++) { // Values in the list should be 1 -> 20 because of sorting
    REQUIRE(testList.getEntry(i) == i+1);
  }

  testList.clear(); // Clear the list

  for (int i=0;i<max;i+=2) { // Insert even values from 0 -> 19
    testList.insert(i);
  }
  for (int i=1;i<max;i+=2) { // Insert odd values from 0 -> 19
    testList.insert(i);
  }
  for (int i=0;i<max;i++) { // List should contain all values from 0 -> 19 in order
    REQUIRE(testList.getEntry(i) == i);
  }


  for (int i=0;i<max;i+=2) { // Remove all the even values from the list from 0 -> 19
    testList.remove(i);
  }
  for (int i=0,j=1;i<testList.getLength();i++,j+=2) { // Check that all the remaining values are the odd values
    REQUIRE(testList.getEntry(i) == j);
  }


  for (int i=0,j=1;i<testList.getLength();i++,j+=2) { // Get position function of all of the existing odd values
    REQUIRE(testList.getPosition(j) == i);
  }
  for (int i=0,j=0;i<testList.getLength();i++,j+=2) { // Get position function of all of the non existing even values
    REQUIRE(testList.getPosition(j) == -i);
  }


  for (int i=1;i<max;i+=2) { // Remove all the remaining odd values
    testList.remove(i);
  }
  REQUIRE(testList.isEmpty()); // Test if the list is now empty

}
