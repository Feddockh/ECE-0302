#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"
#include <iostream>

/*
* This checks the size and validity of the bitset constructor
* This also tests each bit and makes sure it was set to 0
*/
TEST_CASE( "Bitset()", "[bitset]" ) {
    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    for (int i=0;i<8;i++) {
        REQUIRE(b.test(i) == 0);
    }
}

/*
* This tests bitset sizes from 0 to the max
* The size and validity are checked at each size
* For each size, each bit is checked to make sure it equals 0
*/
TEST_CASE( "Bitset(intmax_t size)", "[bitset]" ) {
    int max = 20;
    for (int i=0;i<max;i++){
        Bitset b(i);
        REQUIRE(b.size() == i);
        if (i==0) { REQUIRE(b.good() == false); }
        for (int j=0;j<i;j++) {
            REQUIRE(b.test(j) == 0);
        }
    }
}

/*
* This one is a little tricky, so I will try to explain a bit better
* I create a binary string which will be responsible for setting the constructor later
* This binary string is initialized to all zeros at the beginning of each cycle
* The objective is to check every possible combination between 00000000 to 11111111
* I used the variable i to increment each cycle, and then converted it to a binary string
* I set n = i so that I could perform LSB decimal to binary conversion on n
* Every time the remainder was 1, I replaced the zero in the string with a 1
* Then once I had my binary string, I used it to initialize the constructor
* I then checked each bit of the bitset against the value in the binary string
* I should mention that I was having a lot of issues trying to convert from a string to bool
* Therefore I am converting from a substring --> integer --> bool
* When converting from a character to an int or bool, I had issues because it gave me the ascii value
*/
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
                REQUIRE(b.test(j) == static_cast<bool>(std::stoi(binary.substr(j,1))));
            }
        }
        n = ++i;
    } while (binary != "11111111");
}

// Make sure that we can set with strings over 8 bits
TEST_CASE( "Bitset with string over 8 bits", "[bitset]" ) {
    std::string binary = "101010101"; // 9 bit test string
    Bitset b(binary);
    REQUIRE(b.good());
}

/*
* This tests the destructor and just makes sure that the size goes back to 0
* I can't check the value at each postiion without a runtime error because the memory isn't allocated
*/
TEST_CASE( "~Bitset()", "[bitset]" ) {
    int max = 20;
    for (int i=0;i<max;i++){
        Bitset b(i);  
        b.~Bitset();
        REQUIRE(b.size() == 0);
    }
}

/*
* This creates bitsets from 0 to max size and then checks the size and validity
* Additionally, it checks that each bit is equal to 0
*/
TEST_CASE( "intmax_t size() const", "[bitset]" ) {
    int max = 20;
    for (int i=0;i<max;i++){
        Bitset b(i);
        REQUIRE(b.size() == i);
        if (i==0) { 
            REQUIRE(b.good() == false);
        } else {
            REQUIRE(b.good());
        }
        for (int j=0;j<i;j++) {
            REQUIRE(b.test(j) == 0);
        }
    }
}

/*
* This is testing the validity, and since validity can appear in a few functions, I check each one
* The first loop checks for a true validity after initializing with every string combination of all 0s with a single 1
* The second loop checks for a false validity after initializing with every string combination of all 0s with a single 2
* The third loop sets a bitset of size max and checks that all setting within the max size is true and outside the max size is false
* The fourth loop sets a bitset of size max and checks that all resetting within the max size is true and outside the max size is false
* The fifth loop sets a bitset of size max and checks that all toggles within the max size are true and outside the max size are false
*/
TEST_CASE( "bool good() const", "[bitset]" ) {
    std::string str;
    for (int i=0;i<8;i++) {
        str = "00000000";
        str.replace(i,1,"1");
        SECTION("str = " + str) {
            Bitset b(str);
            REQUIRE(b.good() == true);
        }
    }
    for (int i=0;i<8;i++) {
        str = "00000000";
        str.replace(i,1,"2");
        SECTION("str = " + str) {
            Bitset b(str);
            REQUIRE(b.good() == false);
        }
    }
    int max = 10;
    for (int i=0;i<2*max;i++) {
        Bitset b(max);
        b.set(i);
        REQUIRE(b.good() == (i<max));
    }
    for (int i=0;i<2*max;i++) {
        Bitset b(max);
        b.reset(i);
        REQUIRE(b.good() == (i<max));
    }
    for (int i=0;i<2*max;i++) {
        Bitset b(max);
        b.toggle(i);
        REQUIRE(b.good() == (i<max));
    }
}

/*
* This creates a default bitset and sets a single bit to 1, each cycle the 1 bit is incremented
* Then each bit is checked to be 0 except the bit that was set should be 1
*/
TEST_CASE( "void set(intmax_t index)", "[bitset]" ) {
    for (int i=0;i<8;i++) {
        Bitset b;  
        b.set(i);
        for (int j=0;j<8;j++) {
            REQUIRE(b.test(j)==(i==j));
        }
    }
}

/*
* This creates a bitset which is all 1s and resets a single bit to 0, each cycle the 0 bit is incremented
* Then each bit is checked to be 1 except the bit that was reset should be 0
*/
TEST_CASE( "void reset(intmax_t index)", "[bitset]" ) {
    for (int i=0;i<8;i++) {
        Bitset b("11111111");
        b.reset(i);
        for (int j=0;j<8;j++) {
            REQUIRE(b.test(j)==(i!=j));
        }
    }
}

/*
* First, This creates a default bitset and toggles a single bit to 1, each cycle the 1 bit is incremented
* Then each bit is checked to be 0 except the bit that was toggled should be 1
* Second, This creates a bitset which is all 1s and toggles a single bit to 0, each cycle the 0 bit is incremented
* Then each bit is checked to be 1 except the bit that was toggled should be 0
*/
TEST_CASE( "void toggle(intmax_t index)", "[bitset]" ) {
    for (int i=0;i<8;i++) {
        Bitset b;  
        b.toggle(i);
        for (int j=0;j<8;j++) {
            REQUIRE(b.test(j)==(i==j));
        }
    }
    for (int i=0;i<8;i++) {
        Bitset b("11111111");
        b.toggle(i);
        for (int j=0;j<8;j++) {
            REQUIRE(b.test(j)==(i!=j));
        }
    }
}

/*
* This just initializes the bitset to a string and makes sure we are returning the correct bit value
*/
TEST_CASE( "bool test(intmax_t index)", "[bitset]" ) {
    Bitset b("10101010");
    for (int i=0;i<8;i++) {
        REQUIRE(b.test(i)==(i%2==0));
    }
}

/*
* This is awfully similar to the test that initializes a bitset with a binary string for all possible values
* The only difference is that instead of checking each bit, we check that the strings match
*/
TEST_CASE( "std::string asString() const", "[bitset]" ) {
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
            REQUIRE(b.asString() == binary);
        }
        n = ++i;
    } while (binary != "11111111");
}
