#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"
#include "priority_queue.h"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, DynamicArrayList<int> > SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  int max = 20;

  REQUIRE(pq.isEmpty()); // List should be empty

  for (int i=0;i<max;i+=2) { // Insert even values from 0 -> 19
    pq.add(i);
    REQUIRE(pq.peek() == i); // Max should be the newest addition in this case
  }
  for (int i=1;i<max;i+=2) { // Insert odd values from 0 -> 19
    pq.add(i);
    REQUIRE(pq.peek() >= max-2); // Max should either remain the same or increase to max-1 on the last iteration
  }

  REQUIRE(!pq.isEmpty()); // List should not be empty

  for (int i=max-1;i>=0;i--) { // List should return values from 19 -> 0
    REQUIRE(pq.peek() == i);
    pq.remove();
  }

  REQUIRE(pq.isEmpty()); // List should now be empty
}