#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;
int maxTests = 40;

// creates an object and tests the length and emptyness
TEST_CASE( "Constructor", "[LinkedList]" ) {
  LinkedList<int> list;
  REQUIRE(list.getLength()==0);
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