#include "bitset.hpp"

  Bitset::Bitset() {
      //default construction of a valid bitset of size 8, with all bits set to 0
      N = 8;
      bits = new u_int8_t[N];
  }

  // TODO COMMENT
  Bitset::Bitset(intmax_t size) {
      //construction of a valid bitset of size N, where N is of type intmax_t, with all bits set to 0; the bitset is invalid if N <= 0.
      N = size;
      bits = new u_int8_t[N];
  }

  // TODO COMMENT
  Bitset::Bitset(const std::string & value) {
      //construction of a valid bitset initialized with a string of the form 00010000.
      //If the string contains any character other than 0 or 1, the bitset is invalid.
      N = 8;
      bits = new u_int8_t[N];
      for (int i=0;i<N;i++) {
          int bit = std::stoi(value.substr(i,(i+1)));
          if (bit != 0 || bit != 1) valid = false;
          bits[i] = bit;
      }
  }

  // TODO COMMENT
  Bitset::~Bitset() {
      delete [] bits;
  }

  // TODO COMMENT
  intmax_t Bitset::size() const {
      //a method to return the size of the bitset
      return N;
  }

  // TODO COMMENT
  bool Bitset::good() const {
      //a method to determine if the bitset is valid
      return valid;
  }

  // TODO COMMENT
  void Bitset::set(intmax_t index) {
      //a method to set the nth bit to 1, and if n is not in [0, N-1] then the bitset becomes invalid
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = 1;
      }
  }

  // TODO COMMENT
  void Bitset::reset(intmax_t index) {
      //a method to reset the nth bit to 0, and if n is not in [0, N-1] then the bitset becomes invalid
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = 0;
      }
  }

  // TODO COMMENT
  void Bitset::toggle(intmax_t index) {
      //a method to toggle the nth bit (1 to 0 or 0 to 1), and if n not in [0, N-1] then the bitset becomes invalid
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          bits[index] = !bits[index];
      }
  }

  // TODO COMMENT
  bool Bitset::test(intmax_t index) {
      //a method to check if the nth bit is set (1) by returning a bool value of true if set and false
      //if not, and if n is not in [0, N-1] then the bitset becomes invalid and false is returned
      if (index < 0 || index > (N-1)) {
          valid = false;
      } else {
          return bits[index];
      }
  }

  // TODO COMMENT
  std::string Bitset::asString() const {
      //a method to return the bitset as a std::string of characters 0 and 1. This string should
      //represent the bitset digits from left-to-right with the most significant bit first.
      std::string bitStr;
      for (int i=N;i>=0;i--) {
          char bit = static_cast<char>(bits[i]);
          bitStr.push_back(bit);
      }
      return bitStr;
  }
