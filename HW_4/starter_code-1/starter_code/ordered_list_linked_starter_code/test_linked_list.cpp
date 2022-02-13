/**
 * @file test_linked_list.cpp
 * @author Hayden Feddock
 * @brief test cases for the linked list class object
 * @version 0.1
 * @date 2022-02-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;
int maxTests = 20;

// creates an object and tests the length and emptyness
TEST_CASE( "Constructor", "[LinkedList]" ) {
  LinkedList<int> list;
  REQUIRE(list.getLength()==0);
  REQUIRE(list.isEmpty());
}

// creates an object, fills it, and then uses it to make a new object
TEST_CASE( "Copy Constructor", "[LinkedList]" ) {
  LinkedList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }

  LinkedList<int> list2(list);
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list2.getEntry(i)==i*5);
  }
}

/*
* creates two new objects and fills them both
* overwrites the second list with the first using the = operator
* tests to make sure that the content is the same as from the first list
*/
TEST_CASE( "= Operator", "[LinkedList]" ) {
  LinkedList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  LinkedList<int> list2;
  for (int i=1;i<=maxTests;i++) {
    list2.insert(i, i+2);
  }

  list2 = list;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list2.getEntry(i)==i*5);
  }
}

// swaps two lists
TEST_CASE( "Swap", "[LinkedList]" ) {
  LinkedList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  LinkedList<int> list2;
  for (int i=1;i<=maxTests;i++) {
    list2.insert(i, i+2);
  }

  list.swap(list, list2);
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list.getEntry(i)==i+2);
    REQUIRE(list2.getEntry(i)==i*5);
  }
}

// fills a list while checking emptiness, clearing, and the testing length thoughout
TEST_CASE( "Clear, isEmpty, and getLength", "[LinkedList]" ) {
  LinkedList<int> list;
  REQUIRE(list.isEmpty());
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
    REQUIRE(list.getLength()==i);
  }
  list.clear();
  REQUIRE(list.isEmpty());
}

// inserts a number of items and checks each item after a new one is added
TEST_CASE( "Insert", "[LinkedList]" ) {
  // Inserting onto end
  LinkedList<int> list;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list.insert(i, i*5));
    for (int j=1;j<=i;j++) {
      REQUIRE(list.getEntry(j)==j*5);
    }
  }

  // Inserting into the middle
  LinkedList<int> list2;
  for (int i=1;i<=maxTests;i++) {
    if (i==1) {
      REQUIRE(list2.insert(1, 1));
    } else {
      REQUIRE(list2.insert(i/2, 1));
    }
    for (int j=1;j<=i;j++) {
      REQUIRE(list2.getEntry(j)==1);
    }
  }

  // Inserting onto the front
  LinkedList<int> list3;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list3.insert(1, i));
    for (int j=1;j<=i;j++) {
      REQUIRE(list3.getEntry(j)==i-j+1);
    }
  }
}

// removes items from the end, middle, and front of the list and tests them
TEST_CASE( "Remove", "[LinkedList]" ) {
  LinkedList<int> list;
  // Building list
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  // Removing from the end of the list
  for (int i=maxTests;i>=1;i--) {
    REQUIRE(list.remove(i));
    for (int j=1;j<i;j++) {
      REQUIRE(list.getEntry(j)==j*5);
    }
  }
  REQUIRE(list.isEmpty());
  
  // Rebuilding list
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  // Removing from the center of the list
  for (int i=maxTests;i>1;i--) {
    REQUIRE(list.remove(i/2));
    for (int j=1;j<i;j++) {
      REQUIRE(list.getEntry(j)==(j<(i/2)?j:(j+1+maxTests-i))*5);
    }
  }
  REQUIRE(list.remove(1));
  REQUIRE(list.isEmpty());

  // Rebuilding list
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  // Removing from the front of the list
  for (int i=maxTests;i>=1;i--) {
    REQUIRE(list.remove(1));
    for (int j=1;j<i;j++) {
      REQUIRE(list.getEntry(j)==(j+1+maxTests-i)*5);
    }
  }
}

// fills a new list with values, and then replaces them and tests the new values
TEST_CASE( "getEntry and setEntry", "[LinkedList]" ) {
  LinkedList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }

  for (int i=1;i<=maxTests;i++) {
    list.setEntry(i, 2);
    REQUIRE(list.getEntry(i)==2);
  }
}