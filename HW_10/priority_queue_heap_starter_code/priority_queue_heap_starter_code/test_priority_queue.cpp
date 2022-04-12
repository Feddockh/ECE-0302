#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "heap_priority_queue.h"

TEST_CASE("Test Construction", "[construction]") {
  HeapPriorityQueue<int>  pq;
  REQUIRE(pq.isEmpty());
}

TEST_CASE("Test add", "[add]") {
  HeapPriorityQueue<int>  pq;
  pq.add(25);

  REQUIRE(!pq.isEmpty());
  REQUIRE(pq.peek() == 25);

  pq.add(1);
  REQUIRE(pq.peek() == 25);

  pq.add(78);
  REQUIRE(pq.peek() == 78);
}

TEST_CASE("Test add 2", "[add]") {
  HeapPriorityQueue<int>  pq;

  pq.add(0);
  REQUIRE(pq.peek() == 0);
  
  pq.add(2);
  REQUIRE(pq.peek() == 2);

  pq.add(1);
  REQUIRE(pq.peek() == 2);

  pq.add(3);
  REQUIRE(pq.peek() == 3);

  pq.add(5);
  REQUIRE(pq.peek() == 5);

  pq.add(4);
  REQUIRE(pq.peek() == 5);

  pq.add(7);
  REQUIRE(pq.peek() == 7);

  pq.add(6);
  REQUIRE(pq.peek() == 7);
}


TEST_CASE("Test remove", "[remove]") {
  HeapPriorityQueue<int>  pq;
  pq.add(25);
  pq.add(1);
  pq.add(78);

  pq.remove();
  REQUIRE(pq.peek() == 25);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  pq.remove();
  REQUIRE(pq.isEmpty());
}

TEST_CASE("Test remove 2", "[remove]") {
  HeapPriorityQueue<int>  pq;

  int max = 20;
  for (int i=0;i<max;i++) {
    pq.add(i);
  }

  for (int i=max-1;i>=0;i--) {
    REQUIRE(pq.peek() == i);
    pq.remove();
  }

  REQUIRE(pq.isEmpty());
}

