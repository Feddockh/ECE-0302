// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

XMLParser::XMLParser() {
	tokenized = parsed = false;
}

XMLParser::~XMLParser() {
	clear();
}

bool XMLParser::tokenizeInputString(const std::string &inputString) {

	tokenized = false;

	int i = 0;                                                    // Counter for the input string
	int length = inputString.length();                            // Get the length of the input string
	if (inputString[i] != '<') {                                  // Check that the XML begins with a tag
		clear();
		return false;
	}
	if (inputString[length-1] != '>') {                           // Check that the XML ends with a tag
		clear();
		return false;
	}

	char x;                                                       // Create a varible to hold the character in question

	while (i < length) {                                          // Use a loop to scan through the entire input string

		x = inputString[i];                                       // Set the character

		TokenStruct newToken;                                     // Create the new token to store characters to

		if (x == '<') {                                           // Enter if we begin with a tag '<'

			while (x != '>') {                                    // Copy characters to token until '>' is reached
				newToken.tokenString.push_back(x);                // Add character to the token's string
				x = inputString[++i];                             // Set the next character after incrementing the counter
				
				if (inputString[i] == '<') {                      // Error check for nested '<'
					clear();
					return false;
				}
			}
			newToken.tokenString.push_back(x);                    // Add the '>' character to the token's string
			i++;                                                  // Increment the input string counter

			int tokenLength = newToken.tokenString.length();      // Get the length of the token
			
			// Clasify the type of token
			if (newToken.tokenString[1] == '?') {                 // If the second character is '?' it's a declaration
				if (newToken.tokenString[tokenLength-2] != '?') { // Return false if second to last character is not '?'
					clear();
					return false;
				}
				newToken.tokenType = DECLARATION;
			} else if (newToken.tokenString[1] == '/')            // If the second character is '/' it's an end tag
				newToken.tokenType = END_TAG;
			else if (newToken.tokenString[tokenLength-2] == '/')  // If the second to last character is '/' it's an empty tag
				newToken.tokenType = EMPTY_TAG;
			else                                                  // Otherwise it must be a start tag
				newToken.tokenType = START_TAG;

			tokenizedInputVector.push_back(newToken);             // Push the token onto the token vector
			
		} else {                                                  // We aren't beginning with a tag

			if (x == '>') {                                       // Error check for nested '>'
				clear();
				return false;
			}

			if (x != ' ') {                                       // Begin content if not a blank space

				newToken.tokenType = CONTENT;                     // Therefore we must be beginning with content

				while (x != '<') {                                // Copy characters to token until '<' is reached
					newToken.tokenString.push_back(x);            // Add character to the token's string
					x = inputString[++i];                         // Set the next character after incrementing the counter
				}
			
				tokenizedInputVector.push_back(newToken);         // Push the token onto the token vector

			} else {                                              // Increment past the blank space
				i++;
			}
		}
	}

	tokenized = true;
	return true;
}

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input) {

	int length = input.length();      // Get the length of the string

	char x = input[0];                // Create a character variable for transferring characters
	string tag;                       // Create a string variable to hold the tag characters

	int i = 1;                        // Counter
	while (x != ' ' && x != '>'       // Loop until blank space or '>' or '/'
		&& x != '/' && i < length) {
		tag.push_back(x);             // Add the character to the tag
		x = input[i++];               // Get the next character and then increment the counter
	}

	if (input[length-2] == '/')       // If tag was an empty tag, add back the '/'
		tag.push_back('/');
	
	tag.push_back('>');               // Add the closing '>' to the tag

	return tag;                       // Return the modified tag
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {

	parsed = false;

	if(tokenizedInputVector.empty()) return false; // Return false if the vector is empty

	int tokens = tokenizedInputVector.size(); // Number of tokens

	for (int i=0;i<tokens;i++) { // Loop over each token

		string token = tokenizedInputVector[i].tokenString; // Store the token string to a variable

		int length = token.length();

		string tagName; // Create a tagName string variable

		if (tokenizedInputVector[i].tokenType == CONTENT) continue; // Skip over content

		if (tokenizedInputVector[i].tokenType == DECLARATION) { // Extract declaration tagName
			int i = 2;
			while (token[i] != ' ' && token[i] != '?' && i < length) {
				tagName.push_back(token[i++]);
			}
		}

		if (tokenizedInputVector[i].tokenType == EMPTY_TAG) {
			token = deleteAttributes(token);
			int i = 1;
			while (token[i] != '/' && token[i] != ' ' && i < length) {
				tagName.push_back(token[i++]);
			}
		}

		if (tokenizedInputVector[i].tokenType == START_TAG) {
			token = deleteAttributes(token);
			int i = 1;
			while (token[i] != '>' && token[i] != ' ' && i < length) {
				tagName.push_back(token[i++]);
			}
		}

		if (tokenizedInputVector[i].tokenType == END_TAG) {
			int i = 2;
			while (token[i] != '>' && token[i] != ' ' && i < length) {
				tagName.push_back(token[i++]);
			}
		}

		length = tagName.length(); // Update the length

		// Check the tagName to make sure that it is valid

		/* The name cannot contain any of the following characters: 
		!"#$%&'()*+,/;<=>?@[\]^`{|}~. A tag name cannot contain a space character (no white space), 
		and cannot begin with "-", ".", or a numeric digit. All other Unicode is valid.
		*/

		// In ASCII that is 32-44, 47, 59-64, 91-94, 96, 123-126
		// Can't begin with 45, 46,48-57

		// Convert each character in the tagName to ASCII and check it's validity
		bool valid = true;
		for (int j = 0;j<length;j++) {
			int ascii = static_cast<int>(tagName[j]);
			if (ascii >= 32 && ascii <= 44) valid = false;
			if (ascii == 47) valid = false;
			if (ascii >= 59 && ascii <= 64) valid = false;
			if (ascii >= 91 && ascii <= 94) valid = false;
			if (ascii == 96) valid = false;
			if (ascii >= 123 && ascii <= 126) valid = false;

			if (j == 0) {
				if (ascii == 45) valid = false;
				if (ascii == 46) valid = false;
				if (ascii >= 48 && ascii <= 57) valid = false;
			}

			if (!valid) {
				return false;
			}
		}

		// Once the tagName is deemed valid, check it's nesting
		// If the type is start tag then add to the stack
		if (tokenizedInputVector[i].tokenType == START_TAG) {
			parseStack.push(tagName);
		}

		// If the type is end tag remove from the stack
		if (tokenizedInputVector[i].tokenType == END_TAG) {
			if (tagName != parseStack.peek()) // Check to see if the top entry tagName is equal
				return false; // If not equal, return false
			else
				parseStack.pop(); // If equal tagNames, pop off the tagName
		}

		// Add elements to bag here since they must be valid
		// Don't test for the start tag because that tagName is included in the end tag
		if (tokenizedInputVector[i].tokenType == END_TAG ||
			tokenizedInputVector[i].tokenType == EMPTY_TAG) {
			elementNameBag.add(tagName);
		}
	}

	parsed = true;
	return true;
}

// TODO: Implement the clear method here
void XMLParser::clear() {
	if (!parseStack.isEmpty())
		parseStack.clear();
	if (!elementNameBag.isEmpty())
		elementNameBag.clear();
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const {

	vector<TokenStruct> tokenizedOutputVector;

	int tokens = tokenizedInputVector.size(); // Number of tokens

	for (int i=0;i<tokens;i++) { // Loop over each token

		TokenStruct token;
		token.tokenString = tokenizedInputVector[i].tokenString; // Store the token string to a variable
		token.tokenType = tokenizedInputVector[i].tokenType;

		int length = token.tokenString.length();

		string validTokenString; // Create a valid token string variable

		if (token.tokenType == CONTENT) {
			validTokenString = token.tokenString;
		}

		if (token.tokenType == DECLARATION) { // Extract declaration tagName
			int i = 2;
			while (token.tokenString[i] != '?' && i < length) {
				validTokenString.push_back(token.tokenString[i++]);
			}
		}

		if (token.tokenType == EMPTY_TAG) {
			token.tokenString = deleteAttributes(token.tokenString);
			int i = 1;
			while (token.tokenString[i] != '/' && i < length) {
				validTokenString.push_back(token.tokenString[i++]);
			}
		}

		if (token.tokenType == START_TAG) {
			token.tokenString = deleteAttributes(token.tokenString);
			int i = 1;
			while (token.tokenString[i] != '>' && i < length) {
				validTokenString.push_back(token.tokenString[i++]);
			}
		}

		if (token.tokenType == END_TAG) {
			int i = 2;
			while (token.tokenString[i] != '>' && i < length) {
				validTokenString.push_back(token.tokenString[i++]);
			}
		}

		// Reset the token string with the valid token string
		token.tokenString = validTokenString;

		// Add this token to the output vector
		tokenizedOutputVector.push_back(token);
	}

	return tokenizedOutputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const {
	if (!tokenized || !parsed) return false;
	return elementNameBag.contains(inputString);
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const {
	if (!tokenized || !parsed) return false;
	return elementNameBag.getFrequencyOf(inputString);
}

