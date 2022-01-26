#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>

class Bitset{
public:

  // TODO COMMENT
  Bitset();

  // TODO COMMENT
  Bitset(intmax_t size);

  // TODO COMMENT
  Bitset(const std::string & value);

  // TODO COMMENT
  ~Bitset();

  //I'm pretty sure this just prevents us from being able to copy the class?
  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // TODO COMMENT
  intmax_t size() const;

  // TODO COMMENT
  bool good() const;

  // TODO COMMENT
  void set(intmax_t index);

  // TODO COMMENT
  void reset(intmax_t index);

  // TODO COMMENT
  void toggle(intmax_t index);

  // TODO COMMENT
  bool test(intmax_t index);

  // TODO COMMENT
  std::string asString() const;

private:

  // TODO
  u_int8_t *bits;
  int N;
  bool valid = true;

};

#endif
