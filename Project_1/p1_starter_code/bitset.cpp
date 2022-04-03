#include "bitset.hpp"
#include <iostream>

  //default construction of a valid bitset of size 8, with all bits set to 0    
  Bitset::Bitset() {
      N = 8;
      bits = new u_int8_t[N];
      for (int i=0;i<N;i++)
          bits[i] = 0;
  }

  //construction of a valid bitset of size N, where N is of type intmax_t,
  //with all bits set to 0; the bitset is invalid if N <= 0.
  Bitset::Bitset(intmax_t size) {
      if (size == 0) { valid = false; }
      N = size;
      bits = new u_int8_t[N];
      for (int i=0;i<N;i++)
          bits[i] = 0;
  }

  //construction of a valid bitset initialized with a string of the form 00010000.
  //If the string contains any character other than 0 or 1, the bitset is invalid.
  Bitset::Bitset(const std::string & value) {
      N = value.size();
      bits = new u_int8_t[N];
      for (int i=0;i<N;i++) {
          int bit;
          bit = std::stoi(value.substr(i,1));
          if (bit != 0 && bit != 1) valid = false;
          bits[i] = bit;
      }
  }

  //destructor deletes allocated memory and sets size N to 0
  Bitset::~Bitset() {
      N = 0;
      delete [] bits;
      bits = nullptr;
  }

  //a method to return the size of the bitset
  intmax_t Bitset::size() const {
      return N;
  }

  //a method to determine if the bitset is valid
  bool Bitset::good() const {
      return valid;
  }

  //a method to set the nth bit to 1, and if n is not in [0, N-1] then the bitset becomes invalid
  void Bitset::set(intmax_t index) {
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = 1;
      }
  }

  //a method to reset the nth bit to 0, and if n is not in [0, N-1] then the bitset becomes invalid
  void Bitset::reset(intmax_t index) {
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = 0;
      }
  }

  //a method to toggle the nth bit (1 to 0 or 0 to 1), and if n not in [0, N-1] then the bitset becomes invalid
  void Bitset::toggle(intmax_t index) {
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = !bits[index];
      }
  }

  //a method to check if the nth bit is set (1) by returning a bool value of true if set and false
  //if not, and if n is not in [0, N-1] then the bitset becomes invalid and false is returned
  bool Bitset::test(intmax_t index) {
      if (index < 0 || index > (N-1)) {
          valid = false;
          return -1;
      } else {
          return bits[index];
      }
  }

  //a method to return the bitset as a std::string of characters 0 and 1. This string should
  //represent the bitset digits from left-to-right with the most significant bit first.
  std::string Bitset::asString() const {
      std::string bitStr;
      for (int i=0;i<N;i++)
          bitStr.append((bits[i]==0)?"0":"1");
      return bitStr;
  }
