#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

// Converting postfix to prefix
void convert(string &postfix, string &prefix) {

  // length of postfix
  int length = postfix.size();

  // ch = last character in postfix
  char ch = postfix[length-1];

  // append the last character
  prefix.append(1, ch);

  // base case return
  if (!isoperator(ch)) return;

  // if the last character is an operator
  if (isoperator(ch)) {

    // form of post: <postfix1> <postfix2> <operator>
    // find the beginning of postfix2
    int split = endPost(postfix, length-2);

    // recursively convert postfix1 into prefix form and append
    string postfix1 = postfix.substr(0, split);
    convert(postfix1, prefix);

    // recursively convert postfix2 into prefix form and append
    // the substr function need the length, not the end point
    int postfix2Length = length - split - 1;
    string postfix2 = postfix.substr(split, postfix2Length);
    convert(postfix2, prefix);

  }

  return;
  
}
