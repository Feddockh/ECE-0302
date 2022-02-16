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
	REQUIRE(b.add({"Murder", "for", "a", "jar", "of", "red", "rum"}));
	REQUIRE_FALSE(b.add({"Murder1", "for", "a", "jar", "of", "red", "rum"}));
	REQUIRE_FALSE(b.add({"Murder.", "for", "a", "jar", "of", "red", "rum"}));

	//Test duplicate addition
	REQUIRE_FALSE(b.add({"Red", "rum", "sir", "is", "murder"}));
}

TEST_CASE("Test FindPalindrome recursiveFindPalindromes", "[FindPalindrome]" ) {
	FindPalindrome b;
	// Murder for a jar of red rum
	std::vector<std::string> test = {"red", "a", "jar", "Murder", "of", "rum", "for"};
	REQUIRE(b.add(test));
	std::vector<std::vector<std::string>> result = b.toVector();
	std::vector<std::string> ans1 = {"Murder", "for", "a", "jar", "of", "red", "rum"};
	std::vector<std::string> ans2 = {"red", "rum", "for", "a", "jar", "of", "Murder"};
	bool front = result.front()==ans1 || result.front()==ans2;
	bool back = result.back()==ans1 || result.back()==ans2;
	REQUIRE(front);
	REQUIRE(back);
	REQUIRE(b.number()==2);

	b.clear();
	REQUIRE(b.number()==0);
}

TEST_CASE("Test cutTest1", "[FindPalindrome]" ) {
	FindPalindrome b;

	REQUIRE(b.cutTest1({"Murder", "for", "a", "jar", "of", "red", "rum"}));
	REQUIRE_FALSE(b.cutTest1({"Morder", "for", "a", "jar", "of", "red", "rum"}));
	REQUIRE(b.cutTest1({"Wonton", "not", "now"}));
	REQUIRE_FALSE(b.cutTest1({"Wnnton", "not", "now"}));
}

TEST_CASE("Test cutTest2", "[FindPalindrome]" ) {
	FindPalindrome b;

	REQUIRE(b.cutTest2({"Murder", "for", "a"}, {"jar", "of", "red", "rum"}));
	REQUIRE_FALSE(b.cutTest2({"Murder", "for", "a"}, {"jar", "of", "red", "ram"}));
	REQUIRE(b.cutTest2({"Wonton", "not"}, {"now"}));
	REQUIRE_FALSE(b.cutTest2({"Monton", "not"}, {"now"}));
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
