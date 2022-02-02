/**
 * @file binarySearch.cpp
 * @author Hayden Feddock
 * @brief 
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 */

#include <string>
#include <iostream>

using namespace std;

int binarySearch (const string [], int, int, string);

int main() {
	string list[10] = {"ta", "tb", "tc", "td", "te", "test", "tf", "tg", "th", "ti"};
	cout << "index = " << binarySearch(list, 0, 9, "test") << endl;
}

int binarySearch (const string A[], int first, int last, string target)
{
	int index = 0;
	if (first > last) 
		index = -1; // target not in the original array
	else
{
		int mid = first + (last - first)/2;		// If target is in array, A[first] <= target <= A[last]
		if (target == A[mid])
			index = mid;		// target found at A[mid]
		else if (target < A[mid])
			index = binarySearch(A, first, mid-1, target);
		else
			index = binarySearch(A, mid+1, last, target);
	}
	return index;
}
