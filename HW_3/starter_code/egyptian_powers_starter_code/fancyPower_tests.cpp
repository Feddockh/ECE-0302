#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "fancyPower.hpp"
#include <cmath>
#include <iostream>

// Testing powers from 0 to max for each base from 0 to max
// I found that I cannot increase the max much further past 15 due to sizing
// I did have to adjust the return type of fancyPower from int to long long int to reach higher values
TEST_CASE("Test case", "fancyPower"){
  int max = 10;
  for (int i=0;i<max;i++) {
    for (int j=0;j<max;j++) {
      REQUIRE(fancyPower(j,i) == pow(i,j));
      //std::cout << "for " << i << "^" << j << ", fancyPower = " << fancyPower(j,i) << " and pow = " << pow(i,j) << std::endl;
    }
  }
}