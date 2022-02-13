/**
 * @file test_array_list.cpp
 * @author Hayden Feddock
 * @brief Test cases for the array list class
 * @version 0.1
 * @date 2022-02-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

// force class expansion
template class ArrayList<int>;
int maxTests = 40;

// creates an object and tests the length and emptyness
TEST_CASE( "Constructor", "[ArrayList]" ) {
  ArrayList<int> list;
  REQUIRE(list.getLength()==0);
  REQUIRE(list.isEmpty());
}


// creates an object, fills it, and then uses it to make a new object
TEST_CASE( "Copy Constructor", "[ArrayList]" ) {
  ArrayList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }

  ArrayList<int> list2 = list;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list2.getEntry(i)==i*5);
  }
}

/*
* creates two new objects and fills them both
* overwrites the second list with the first using the = operator
* tests to make sure that the content is the same as from the first list
*/
TEST_CASE( "= Operator", "[ArrayList]" ) {
  ArrayList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }
  ArrayList<int> list2;
  for (int i=1;i<=maxTests;i++) {
    list2.insert(i, i+2);
  }

  list2 = list;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list2.getEntry(i)==i*5);
  }
}

// fills a list while checking emptiness, clearing, and the testing length thoughout
TEST_CASE( "Clear, isEmpty, and getLength", "[ArrayList]" ) {
  ArrayList<int> list;
  REQUIRE(list.isEmpty());
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
    REQUIRE(list.getLength()==i);
  }
  list.clear();
  REQUIRE(list.isEmpty());
}

// inserts a number of items and checks each item after a new one is added
TEST_CASE( "Insert", "[ArrayList]" ) {
  // Inserting onto end
  ArrayList<int> list;
  for (int i=1;i<=maxTests;i++) {
    REQUIRE(list.insert(i, i*5));
    for (int j=1;j<=i;j++) {
      REQUIRE(list.getEntry(j)==j*5);
    }
  }
}

// removes items from the end, middle, and front of the list and tests them
TEST_CASE( "Remove", "[ArrayList]" ) {
  ArrayList<int> list;
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
TEST_CASE( "getEntry and setEntry", "[ArrayList]" ) {
  ArrayList<int> list;
  for (int i=1;i<=maxTests;i++) {
    list.insert(i, i*5);
  }

  for (int i=1;i<=maxTests;i++) {
    list.setEntry(i, 2);
    REQUIRE(list.getEntry(i)==2);
  }
}