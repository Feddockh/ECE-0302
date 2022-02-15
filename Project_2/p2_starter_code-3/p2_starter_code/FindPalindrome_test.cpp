#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test FindPalindrome add (string)", "[FindPalindrome]" )
{
	FindPalindrome b;
	// Test bad additions
	REQUIRE_FALSE(b.add("kayak1"));
	REQUIRE_FALSE(b.add("kayak."));
	REQUIRE_FALSE(b.add("kayak!"));
	REQUIRE_FALSE(b.add("kayak@"));
	REQUIRE_FALSE(b.add("kayak."));
	REQUIRE_FALSE(b.add("kayak["));
	REQUIRE_FALSE(b.add("kayak'"));
	REQUIRE_FALSE(b.add("kayak{"));

	// Test valid addition
	REQUIRE(b.add("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));

	//Test duplicate addition
	REQUIRE(b.add("kayak"));
	REQUIRE_FALSE(b.add("kayak"));
}

TEST_CASE("Test FindPalindrome add (vector string)", "[FindPalindrome]" ) {
	FindPalindrome b;
	std::vector<std::string> goodStringVector = {"Murder", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE(b.add(goodStringVector));
	std::vector<std::string> badStringVector1 = {"Murder1", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE_FALSE(b.add(badStringVector1));
	std::vector<std::string> badStringVector2 = {"Murder.", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE_FALSE(b.add(badStringVector2));

	//Test duplicate addition
	std::vector<std::string> duplicateStringVector = {"Red", "rum", "sir", "is", "murder"};
	REQUIRE_FALSE(b.add(duplicateStringVector));
}

TEST_CASE("Test FindPalindrome recursiveFindPalindromes", "[FindPalindrome]" ) {
	FindPalindrome b;
	std::vector<std::string> test = {"Murder", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE(b.add(test));
	std::vector<std::vector<std::string>> result = b.toVector();
	REQUIRE(result.front()==test);
}

TEST_CASE("Test cutTest1", "[FindPalindrome]" ) {
	FindPalindrome b;
	std::vector<std::string> goodTest1 = {"Murder", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE(b.cutTest1(goodTest1));
	std::vector<std::string> badTest1 = {"Morder", "for", "a", "jar", "of", "red", "rum"};
	REQUIRE_FALSE(b.cutTest1(badTest1));
	std::vector<std::string> goodTest2 = {"Wonton", "not", "now"};
	REQUIRE(b.cutTest1(goodTest2));
	std::vector<std::string> badTest2 = {"Wnnton", "not", "now"};
	REQUIRE_FALSE(b.cutTest1(badTest2));
}

/*
* Murder for a jar of red rum
* dont nod
* evil olive
* amore Roma
* Yo bannana boy
* dammit Im mad
* Borrow or rob
* I did did I
* Draw O coward
* Wonton Not now
* Never odd or even
* Step on no pets
* Live not on evil
* Rise to vote sir
* Stella won no wallets
* Wont lovers revolt now
* Delia Saw I was ailed
* Too bad I hid a boot
* Red rum sir is murder
* Nate bit a Tibetan
* Ah Satan sees Natasha
*/
