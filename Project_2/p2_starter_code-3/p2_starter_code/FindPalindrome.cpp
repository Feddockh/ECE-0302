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
	int vectorBagSize = currentStringVector.size();

	// Test the size for the base case
	if (vectorBagSize==0) {

		// We want to concatenate the candidate vector of strings that we have to a string
		string candiateStr;
		for (int i=0;i<candidateStringVector.size();i++) {
			candiateStr.append(candidateStringVector[i]);
		}

		// If the candidate string is a palindrome, add it to the vector of vector strings
		if (isPalindrome(candiateStr)) {
			palindromesBag.push_back(candidateStringVector);
			numberOfPalindromes++;
		}

		// Return once the base case is completed
		return;
	}

	// Loop through adding each of the string vectors to the candidate string vector
	// The base case of the recursive call will skip past this loop because size = 0
	for (int i=0;i<vectorBagSize;i++) {

		// Create two new string vectors which we can modify and use
		vector<string> newCandidateStringVector = candidateStringVector;
		vector<string> newCurrentStringVector;
		
		// Add element i from the current string vector to the candidate string vector
		newCandidateStringVector.push_back(currentStringVector[i]);

		// Copy over all elements but i to the new current string vector
		for (int j=0;j<vectorBagSize;j++) {
			if (j!=i) newCurrentStringVector.push_back(currentStringVector[j]);
		}

		// Implemet cut test 2 here to potentially save time
		if (cutTest2(newCandidateStringVector, newCurrentStringVector)) {

			// Recursively call the function with the modified vectors
			recursiveFindPalindromes(newCandidateStringVector, newCurrentStringVector);

		}
	}
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

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	// Determine which string is longer
	// Set longer and shorter strings with the concatenated strings from the vectors
	string longStr, shortStr;

	/*                            ERROR CAUGHT
	* I had a really big bug that I tracked down to here and fixed
	* I was determining the long and short strings by using the size function 
	* on the vector<string> which was returning the number of words, but I was
	* expecting the number of characters to be returned, so I should've been making
	* the vector<string> a string first, and then using the .size() function 
	*/

	// Lets assume that the string vector 1 is larger first and make the strings
	for (int i=0;i<stringVector1.size();i++) longStr += stringVector1[i];
	for (int i=0;i<stringVector2.size();i++) shortStr += stringVector2[i];

	// Test whether our guess was right, if not we can swap the data with that of the short string
	if (longStr.size()<shortStr.size()) longStr.swap(shortStr);

	// The vector of type string will look something like: "a", "AaA", "aA"
	// Convert to lowercase to compare
	convertToLowerCase(longStr);
	convertToLowerCase(shortStr);

	// All of the characters from the smaller string must appear in the larger one
	// Create an int array to keep track of character a-z occurances
	// Initialize all values in the array to zero
	int characterCount[26];
	for (int i=0;i<26;i++) characterCount[i] = 0;

	// Use ascii values to increment array positions corresponding to each letter in the long string
	for (int i=0;i<longStr.size();i++) {
		int x = static_cast<int>(longStr[i]);
		characterCount[x-97]++;
	}

	// Move through the short string, convert characters to ascii, and compare to the array
	// If the character position in the array has not already been set, then return false
	bool cut = false;
	for (int i=0;i<shortStr.size();i++) {
		int x = static_cast<int>(shortStr[i]);
		if (characterCount[x-97]==0) return false;
	}

	return true;
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
		string lowerCaseValue = value;
		string lowerCaseBag = wordBag[i];
		convertToLowerCase(lowerCaseValue);
		convertToLowerCase(lowerCaseBag);
		if (lowerCaseValue == lowerCaseBag) return false;
	}

	// If the string is valid, add it to the word bag
	wordBag.push_back(value);

	// Implement cut test 1 here to potentially save time
	// If the letters in wordBag don't add up, then don't call the recursive function
	if (!cutTest1(wordBag)) return true;

	// Clear the current palindromes and reset the number of palindromes to 0
	palindromesBag.clear();
	numberOfPalindromes = 0;

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

	// Test whether there are duplicates within the string vector
	for (int i=0;i<stringVector.size();i++) {
		string lowerCaseValue1 = stringVector[i];
		convertToLowerCase(lowerCaseValue1);
		for (int j=0;j<stringVector.size();j++) {
			if (i!=j) {
				string lowerCaseValue2 = stringVector[j];
				convertToLowerCase(lowerCaseValue2);
				if (lowerCaseValue1 == lowerCaseValue2) return false;
			}
		}
	}

	// Testing whether a word already exists in the bag
	for (int i=0;i<stringVector.size();i++) {
		string lowerCaseValue = stringVector[i];
		convertToLowerCase(lowerCaseValue);
		for (int j=0;j<wordBag.size();j++) {
			string lowerCaseBag = wordBag[j];
			convertToLowerCase(lowerCaseBag);
			if (lowerCaseValue == lowerCaseBag) return false;
		}
	}

	// If the vector of strings is valid, add it to the vector
	for (int i=0;i<stringVector.size();i++) {
		wordBag.push_back(stringVector[i]);
	}

	// Implement cut test 1 here to potentially save time
	// If the letters in wordBag don't add up, then don't call the recursive function
	if (!cutTest1(wordBag)) return true;

	// Clear the current palindromes and reset the number of palindromes to 0
	palindromesBag.clear();
	numberOfPalindromes = 0;

	// Recalculate the palindromes
	vector<string> candidateStringVector;
	recursiveFindPalindromes(candidateStringVector, wordBag);

	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	return palindromesBag;
}