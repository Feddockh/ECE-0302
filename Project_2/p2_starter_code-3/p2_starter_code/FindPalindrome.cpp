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

		// Create new string vectors to copy the vectors we are about to modify
		vector<string> newCandidateStringVector = candidateStringVector;
		vector<string> newCurrentStringVector = currentStringVector;

		// Add the last element from the current string vector to the candidate string vector
		// Delete the last element of the current string vector
		newCandidateStringVector.push_back(newCurrentStringVector.back());
		newCurrentStringVector.pop_back();
		
		// Recursively call the function with the modified vectors
		recursiveFindPalindromes(newCandidateStringVector, newCurrentStringVector);
	}

	// Now we are past the function call and in the base case
	if (size==0) {

		// We want to concatenate the candidate vector of strings that we have to a string
		string candiate;
		for (int i=0;i<candidateStringVector.size();i++) {
			candiate.append(candidateStringVector[i]);
		}

		// Test to see if the candidate string is a palindrome
		if (isPalindrome(candiate)) {
			palindromes.push_back(candidateStringVector);
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
	// TODO need to implement this...
}

FindPalindrome::~FindPalindrome()
{
	// TODO need to implement this...
}

int FindPalindrome::number() const
{
	return numberOfPalindromes;
}

void FindPalindrome::clear()
{
	palindromes.clear();
	vectorOfStrings.clear();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// Get the number of strings
	// Use the number of strings to concatenate all of the strings
	int vectorSize = stringVector.size();
	string str;
	for (int i=0;i<vectorSize;i++) {
		str += stringVector[i];
	}

	// The vector of type string will look something like: "a", "AaA", "aA"
	// Convert to lowercase to compare
	convertToLowerCase(str);

	// This bool will be used later for odd string length testing
	bool oddNum = false;

	// Loop testing with each letter of the string
	int strSize = str.size();
	for (int i=0;i<strSize;i++) {

		// Select a letter for comparison and count it's occurances
		char letter = str[i];
		int letterOccurances = 0;

		// Loop through the string with the selected letter
		// If the letter is founc, increment the number of letter occurances
		for (int j=0;i<strSize;i++) {
			if (str[j]==letter) letterOccurances++;
		}

		// If the number is even, each letter should be repeated an even number of times
		// If the number is odd, only one letter should be repeated an odd number of times
		if (strSize%2==0) {
			if (letterOccurances%2!=0) return false;
		} else {
			if (oddNum) return false;
			if (letterOccurances%2!=0) oddNum = true;
		}
	}

	return true;
}

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
	vectorOfStrings.push_back(value);
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	for (int i=0;i<stringVector.size();i++) {
		vectorOfStrings.push_back(stringVector[i]);
	}
	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// TODO need to implement this...
	vector<vector<string>> returnThingie;
	return returnThingie;
}