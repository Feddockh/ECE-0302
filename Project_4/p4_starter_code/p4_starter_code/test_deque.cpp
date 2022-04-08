#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

// Test file is named "student-tests"

TEST_CASE( "Test", "[deque]" ) {
    Deque<int> D;

    // Deque should be empty
    REQUIRE(D.isEmpty());

    // Test exceptions for popping an empty deque
    bool success;
    try {
        D.popFront();
        success = false;
    } catch (const std::exception& e) {
        success = true;
    }
    REQUIRE(success);

    try {
        D.popBack();
        success = false;
    } catch (const std::exception& e) {
        success = true;
    }
    REQUIRE(success);

    // Test exception for accessing an empty deque
    try {
        D.front();
        success = false;
    } catch (const std::exception& e) {
        success = true;
    }
    REQUIRE(success);

    try {
        D.back();
        success = false;
    } catch (const std::exception& e) {
        success = true;
    }
    REQUIRE(success);

    // Test pushing values 0 --> 20 to the front and back of a deque at the same time
    int max = 20;
    for (int i=0;i<max;i++) {
        D.pushFront(i);
        D.pushBack(i);
    }
    REQUIRE(!D.isEmpty());

    // Check that as we pop values from the front and back, both the front and back go from 20 to 0
    for (int i=19;i>=0;i--) {
        REQUIRE(D.front() == i);
        D.popFront();
        REQUIRE(D.back() == i);
        D.popBack();
    }
    REQUIRE(D.isEmpty());
}
