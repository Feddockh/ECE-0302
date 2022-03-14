#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

int static maxSize = 20;

/******************************* TESTS FOR Stack *******************************/

TEST_CASE( "Test Bag Add", "[XMLParser]" ) {

	Bag<int> intBag;               // Define bag of ints
	int size;                      // Define the size
	bool success;                  // Define the outcome

	for (int i=0; i<maxSize; i++) {    // Loop until max

		success = intBag.add(i);   // Confirm items can be added to bag
		REQUIRE(success);

		size = intBag.size();      // Return the size of the bag
		success = (size == (i+1)); // Confirm the number of items in the bag
		REQUIRE(success);
	}
}

TEST_CASE( "Test Stack Push", "[XMLParser]" ) {

	Stack<int> intStack;            // Define stack of ints
	int size;                       // Define the size
	bool success;                   // Define the outcome

	for (int i=0; i<maxSize; i++) { // Loop until max

		success = intStack.push(i); // Confirm items can be pushed to the stack
		REQUIRE(success);

		size = intStack.size();     // Return the size of the stack
		success = (size == (i+1));  // Confirm the size of the stack
		REQUIRE(success);
	}
}

TEST_CASE( "Test Stack Peek", "[XMLParser]" ) {

	Stack<int> intStack;               // Define a stack of ints

	for (int i=0; i<maxSize; i++) {    // Loop until max

		intStack.push(i);              // Push items to stack

		REQUIRE(intStack.peek() == i); // Confirm that peek works
	}

	intStack.clear();                  // Clear the stack

	REQUIRE(intStack.peek() == NULL);  // Confirm that peek returns null when stack is empty
}

TEST_CASE( "Test Stack Pop", "[XMLParser]" ) {

	Stack<int> intStack;                         // Define a stack of ints

	for (int i=0; i<maxSize; i++) {              // Loop until max
		
		intStack.push(i);                        // Push items to stack
	}

	for (int i=0; i<maxSize; i++) {              // Loop until max

		REQUIRE(intStack.peek() == maxSize-i-1); // Confirm that peek works

		REQUIRE(intStack.pop());                 // Confirm we can pop items from stack
	}

	REQUIRE(!intStack.pop());                    // Confirm that we cannot pop when the stack is empty
}

TEST_CASE( "Test Stack Size, Clear, and isEmpty", "[XMLParser]" ) {

	Stack<int> intStack;              // Define a stack of ints
	int size;                         // Define the size

	for (int i=0; i<maxSize; i++) {   // Loop until max
		
		intStack.push(i);             // Push items to stack

		size = intStack.size();       // Get the size
		REQUIRE(size == i+1);         // Confirm the size

		REQUIRE(!intStack.isEmpty()); // Confirm that the stack isn't empty
	}

	intStack.clear();                 // Clear the stack

	REQUIRE(intStack.isEmpty());      // Confirm that the stack is now empty
}

TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}

/******************************* TESTS FOR XMLParser *******************************/

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" ) {

	XMLParser myXMLParser;                                                  // Define XMLParser

	INFO("Test valid string 1");
	string testString = "<test>stuff</test>";                               // Define a valid test string
	REQUIRE(myXMLParser.tokenizeInputString(testString));                   // Confirm that a valid string can be parsed
	std::vector<TokenStruct> result = {                                     // Define the expected result
		TokenStruct{StringTokenType::START_TAG, std::string("test")},
		TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
		TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();    // Return the vector from the object
	REQUIRE(result.size() == output.size());                                 // Check that the sizes of the vectors match
	for (int i = 0; i < result.size(); i++) {                                // Check that each token matches the expected token
		REQUIRE(result[i].tokenType == output[i].tokenType);
		REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
	}

	myXMLParser.clear();                                                     // Clear the object

	INFO("Test valid string 2");
	testString = "<?declaration?><test><test2><test3/></test2>stuff</test>"; // Define a valid test string
	REQUIRE(myXMLParser.tokenizeInputString(testString));                    // Confirm that a valid string can be parsed
	result = { // Define the expected result
		TokenStruct{StringTokenType::DECLARATION, std::string("declaration")},
		TokenStruct{StringTokenType::START_TAG, std::string("test")},
		TokenStruct{StringTokenType::START_TAG, std::string("test2")},
		TokenStruct{StringTokenType::EMPTY_TAG, std::string("test3")},
		TokenStruct{StringTokenType::END_TAG, std::string("test2")},
		TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
		TokenStruct{StringTokenType::END_TAG, std::string("test")}};
	output = myXMLParser.returnTokenizedInput();                              // Return the vector from the object
	REQUIRE(result.size() == output.size());                                  // Check that the sizes of the vectors match
	for (int i = 0; i < result.size(); i++) {                                 // Check that each token matches the expected token
		REQUIRE(result[i].tokenType == output[i].tokenType);
		REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
	}

	myXMLParser.clear();                                                      // Clear the object

	std::vector<std::string> invalidTests = {                                 // Define vector of possible invalid strings
		{"<<test>stuff</test>"}, 
		{"<test>>stuff</test>"},
		{"<test>stuff<</test>"},
		{"<test>stuff</test>>"},
		{"test>stuff</test>"},
		{"<teststuff</test>"},
		{"<test>stuff/test>"},
		{"<test>stuff</test"},
	};

	// TODO: Error on i = 6
	INFO("Test invalid strings");
	for (int i=0; i<invalidTests.size(); i++) {                               // Loop over all invalid strings in the vector
		bool success = myXMLParser.tokenizeInputString(invalidTests[i]);      // Confirm that an invalid string cannot be tokenized
		REQUIRE(!success); 
		std::vector<TokenStruct> result;                                      // Define the expected result
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput(); // Return the vector from the object
		REQUIRE(result.size() == output.size());                              // Check that the sizes of the vectors match
		for (int i = 0; i < result.size(); i++) {                             // Check that each token matches the expected token
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
		myXMLParser.clear();
	}
}

/*


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	   INFO("Hint: tokenize multiple elements test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									TokenStruct{StringTokenType::START_TAG, std::string("From")},
									TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									TokenStruct{StringTokenType::END_TAG, std::string("From")},
									TokenStruct{StringTokenType::START_TAG, std::string("To")},
									TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									TokenStruct{StringTokenType::END_TAG, std::string("To")},
									TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
	   INFO("Hint: Product");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		//cout << inputString;

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}

*/