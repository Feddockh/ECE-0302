#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------

// non-class helper functions go here, should be declared as "static" so that
// their scope is limited

// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{
	// Create an int to keep track of our current string vector's size
	int size = currentStringVector.size();

	// Loop through adding each of the string vectors to the candidate string vector
	// The base case of the recursive call will skip past this loop because size = 0
	for (int i=0;i<size;i++) {

		// Create two new string vectors which we can modify and use
		vector<string> newCandidateStringVector = candidateStringVector;
		vector<string> newCurrentStringVector;
		
		// Add element i from the current string vector to the candidate string vector
		newCandidateStringVector.push_back(currentStringVector[i]);

		// Copy over all elements but i to the new current string vector
		for (int j=0;j<size;j++) {
			if (j!=i) newCurrentStringVector.push_back(currentStringVector[j]);
		}
		
		// Recursively call the function with the modified vectors
		recursiveFindPalindromes(newCandidateStringVector, newCurrentStringVector);
	}

	// Now we are past the function call and in the base case
	if (size==0) {

		//Implement cut test 1 here to potentially save time
		if (!cutTest1(candidateStringVector)) return;

		// We want to concatenate the candidate vector of strings that we have to a string
		string candiate;
		for (int i=0;i<candidateStringVector.size();i++) {
			candiate.append(candidateStringVector[i]);
		}

		// If the candidate string is a palindrome, add it to the vector of vector strings
		if (isPalindrome(candiate)) {
			palindromesBag.push_back(candidateStringVector);
			numberOfPalindromes++;
		}
	}

	return;
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	numberOfPalindromes = 0;
}

FindPalindrome::~FindPalindrome()
{
	clear();
}

int FindPalindrome::number() const
{
	return numberOfPalindromes;
}

void FindPalindrome::clear()
{
	palindromesBag.clear();
	wordBag.clear();
	numberOfPalindromes = 0;
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// Concatenate all of the strings into str
	string str;
	for (int i=0;i<stringVector.size();i++) {
		str += stringVector[i];
	}

	// The vector of type string will look something like: "a", "AaA", "aA"
	// Convert to lowercase to compare
	convertToLowerCase(str);

	// Create an int array to keep track of character a-z occurances
	// Initialize all values in the array to zero
	int characterCount[26];
	for (int i=0;i<26;i++) characterCount[i] = 0;

	// Use ascii values to increment positions in the array corresponding to the letter
	int size = str.size();
	for (int i=0;i<size;i++) {
		int x = static_cast<int>(str[i]);
		characterCount[x-97]++;
	}

	// Determine if the length of the array is even or odd
	bool lengthIsEven = (size%2==0);

	//Count the number of odd numbers in the character array
	int oddNums = 0;
	for (int i=0;i<26;i++) {

		// Tally all of the odd numbers from the character array
		oddNums += (characterCount[i]%2==1);

		// If the length is even, each letter should be repeated an even number of times
		if (oddNums!=0 && lengthIsEven) return false;

		// If the number is odd, only one letter should be repeated an odd number of times
		if (oddNums>1 && !lengthIsEven) return false;
	}

	// If all tests are passed return true
	return true;
}

// TODO redo this test with a similar method to the first one
bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{

	// All of the characters from the smaller string must appear in the larger one
	// Determine which string is longer
	int vectorSize1 = stringVector1.size();
	int vectorSize2 = stringVector2.size();

	// Find out which vector is longer
	string longStr, shortStr;
	int longSize, shortSize;
	if (vectorSize1>vectorSize2) {

		// Make the long string from vector 1
		longSize = vectorSize1;
		for (int i=0;i<longSize;i++) {
			longStr += stringVector1[i];
		}

		// Make the short string from vector 2
		shortSize = vectorSize2;
		for (int i=0;i<shortSize;i++) {
			shortStr += stringVector2[i];
		}

	} else {

		// Make the long string from vector 2
		longSize = vectorSize2;
		for (int i=0;i<longSize;i++) {
			longStr += stringVector2[i];
		}

		// Make the short string from vector 1
		shortSize = vectorSize1;
		for (int i=0;i<shortSize;i++) {
			shortStr += stringVector1[i];
		}
	}
	
	// The vector of type string will look something like: "a", "AaA", "aA"
	// Convert to lowercase to compare
	convertToLowerCase(longStr);
	convertToLowerCase(shortStr);

	// Loop testing with each letter of the shorter string
	for (int i=0;i<shortSize;i++) {

		// Select a letter from the shorter string for comparison and count it's occurances
		char letter = shortStr[i];
		int letterOccurances = 0;

		// Loop through the longer string with the selected letter from the shorter string
		// If the letter is found, increment the number of letter occurances
		for (int j=0;i<longSize;i++) {
			if (longStr[j]==letter) letterOccurances++;
		}

		// If there is no occurance of the letter in the longer string, return false
		if (letterOccurances==0) return false;
	}

	return false;
}

bool FindPalindrome::add(const string & value)
{
	// Testing whether the string has valid characters using ascii values
	for (int i=0;i<value.size();i++) {
		int x = static_cast<int>(value[i]);
		if (x<65 || (x>90 && x<97) || x>122) return false;
	}

	//Testing whether a word already exists in the bag
	for (int i=0;i<wordBag.size();i++) {
		if (value == wordBag[i]) return false;
	}

	// If the string is valid, add it to the word bag
	wordBag.push_back(value);

	// Clear the current palindromes
	palindromesBag.clear();

	// Recalculate the palindromes
	vector<string> candidateStringVector;
	recursiveFindPalindromes(candidateStringVector, wordBag);

	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	// Testing whether each string in the vector has valid characters using ascii values
	for (int i=0;i<stringVector.size();i++) {
		string value = stringVector[i];
		for (int j=0;j<value.size();j++) {
			int x = static_cast<int>(value[j]);
			if (x<65 || (x>90 && x<97) || x>122) return false;
		}
	}

	//Testing whether a word already exists in the bag
	for (int i=0;i<stringVector.size();i++) {
		for (int j=0;j<wordBag.size();j++) {
			if (stringVector[i] == wordBag[j]) return false;
		}
	}

	// If the vector of strings is valid, add it to the vector
	for (int i=0;i<stringVector.size();i++) {
		wordBag.push_back(stringVector[i]);
	}

	// Clear the current palindromes
	palindromesBag.clear();

	// Recalculate the palindromes
	vector<string> candidateStringVector;
	recursiveFindPalindromes(candidateStringVector, wordBag);

	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromesBag;
}