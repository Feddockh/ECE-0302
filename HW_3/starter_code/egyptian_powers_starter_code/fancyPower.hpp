/**
 * @file fancyPower.hpp
 * @author Hayden Feddock
 * @brief function that computes powers by recurance relation
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FANCYPOWER_HPP
#define FANCYPOWER_HPP

// Following "Egyptian Powers" algorithm
// n is the power and m is the base, both should be integers
// long long int return type to accomadate a larger range of calculations
long long int fancyPower(int n, int m)
{
	// Returns 1 for the base case
	if (n==0) return 1;

	// If even, parameters for recursive call will be n divided by 2 and m squared
	// If odd, multiply recursive call by m, parameters for recursive call will be n-1 divided by 2 and m squared
	if (n%2==0)
		return fancyPower(n/2,m*m);
	else {
		return m * fancyPower((n-1)/2,m*m);
	}
	
	/*
	Alternative way I was able to achieve the correct results
	if (n>0)
		return m * fancyPower(n-1, m);
	else 
		return 1;
	*/
}

#endif
