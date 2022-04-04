#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

// Test file is named "student-tests"

TEST_CASE( "Test", "[deque]" ) {
    Deque<int> D;

    REQUIRE(D.isEmpty());

    int max = 20;

    for (int i=0;i<max;i++) {
        D.pushFront(i);
        D.pushBack(i);
    }

    REQUIRE(!D.isEmpty());

    for (int i=19;i>=0;i--) {
        REQUIRE(D.front() == i);
        D.popFront();
        REQUIRE(D.back() == i); // Error here
        D.popBack();
    }

    REQUIRE(D.isEmpty());
}
