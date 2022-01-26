#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"
#include <iostream>

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Bitset()", "[bitset]" ) {
    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    for (int i=0;i<8;i++) {
        REQUIRE(b.test(i) == 0);
    }
}

TEST_CASE( "Bitset(intmax_t size)", "[bitset]" ) {
    int max = 20;
    for (int i=0;i<max;i++){
        Bitset b(i);  
        REQUIRE(b.size() == i);
        REQUIRE(b.good());
        for (int j=0;j<i;j++) {
            REQUIRE(b.test(j) == 0);
        }
    }
}

TEST_CASE( "Bitset(const std::string & value)", "[bitset]" ) {
    int n = 0,i = 0;
    std::string binary;
    do {
        binary = "00000000";
        for (int j=0;j<8;j++) {
            if (n%2==1) binary.replace(7-j,1,"1");
            n/=2;
        }

        Bitset b(binary);
        SECTION("binary = " + binary + " = " + std::to_string(i) + " = " + b.asString()) {
            for (int j=0;j<8;j++) {
                SECTION("j = " + std::to_string(j))
                REQUIRE(b.test(j) == static_cast<bool>(binary.at(j)));
            }
        }
        n = ++i;
    } while (binary != "11111111");
}

/*
TEST_CASE( "~Bitset()", "[bitset]" ) {
    int max = 20;
    for (int i=0;i<max;i++){
        Bitset b(i);  
        b.~Bitset();
        REQUIRE(b.size() == 0);
        for (int j=0;j<8;j++) {
            REQUIRE(b.test(j) != 0);
        }
    }
}
*/

TEST_CASE( "intmax_t size() const", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "bool good() const", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "void set(intmax_t index)", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "void reset(intmax_t index)", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "void toggle(intmax_t index)", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "bool test(intmax_t index)", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "std::string asString() const", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}
