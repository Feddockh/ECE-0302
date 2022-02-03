/**
 * @file limited_size_bag_tests.cpp
 * @author Hayden Feddock
 * @brief Tests for the LimitedSizeBag class and it's methods
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Test Construction/Destruction", "[LimitedSizeBag]"){

  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
}

TEST_CASE("Test Copy Construction", "[LimitedSizeBag]") {
  int max = LimitedSizeBag<int>::MAXSIZE;
  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for (int i=0;i<max;i++) {
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  LimitedSizeBag<int> c(b);
  REQUIRE(c.getCurrentSize() == max);
  REQUIRE(!c.isEmpty());

  for (int i=0;i<max;i++) {
    REQUIRE(c.getFrequencyOf(i) == 1);
    REQUIRE(c.getCurrentSize() == max-i);
    REQUIRE(c.remove(i));
  }
}

TEST_CASE("Test = Operator", "[LimitedSizeBag]") {
  int max = LimitedSizeBag<int>::MAXSIZE;
  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for (int i=0;i<max;i++) {
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  LimitedSizeBag<int> c;
  c = b;
  REQUIRE(c.getCurrentSize() == max);
  REQUIRE(!c.isEmpty());

  for (int i=0;i<max;i++) {
    REQUIRE(c.getFrequencyOf(i) == 1);
    REQUIRE(c.getCurrentSize() == max-i);
    REQUIRE(c.remove(i));
  }
}

TEST_CASE("Test add", "[LimitedSizeBag]"){

  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }
  REQUIRE(!b.add(0));
}

TEST_CASE("Test remove", "[LimitedSizeBag]"){

  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  REQUIRE(!b.remove(-1));
  
  for(int i = 0; i <  LimitedSizeBag<int>::MAXSIZE; ++i){
    REQUIRE(b.remove(i));
  }
  REQUIRE(!b.remove(0));
}

TEST_CASE("Test clear", "[LimitedSizeBag]"){

  LimitedSizeBag<int> b;
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());

  for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
    REQUIRE(b.add(i));
    REQUIRE(b.getCurrentSize() == i+1);
    REQUIRE(!b.isEmpty());
  }

  b.clear();
  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  
}

TEST_CASE("Test frequency", "[LimitedSizeBag]"){

  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(b.getFrequencyOf(0) == 0);
    
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.getFrequencyOf(i) == 1);
    }
  }
  
  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    std::size_t EXPECTED = LimitedSizeBag<int>::MAXSIZE;
    REQUIRE(b.getFrequencyOf(-1) == EXPECTED);
    REQUIRE(b.getFrequencyOf(0) == 0);
  }
}


TEST_CASE("Test contains", "[LimitedSizeBag]"){

  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
	
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.add(i));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }
    
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.contains(i));
    }
    REQUIRE(!b.contains(-1));
  }
  
  {
    LimitedSizeBag<int> b;
    REQUIRE(b.getCurrentSize() == 0);
    REQUIRE(b.isEmpty());
    REQUIRE(!b.contains(0));
    
    for(int i = 0; i < LimitedSizeBag<int>::MAXSIZE; ++i){
      REQUIRE(b.add(-1));
      REQUIRE(b.getCurrentSize() == i+1);
      REQUIRE(!b.isEmpty());
    }

    REQUIRE(b.contains(-1));
    REQUIRE(!b.contains(0));
  }
}