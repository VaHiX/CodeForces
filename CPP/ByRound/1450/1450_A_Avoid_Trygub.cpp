// Problem: CF 1450 A - Avoid Trygub
// https://codeforces.com/contest/1450/problem/A

/*
Code Purpose:
This code solves the problem of reordering the characters of a given string such that the sequence "trygub" does not appear as a subsequence. 
The approach taken is to sort the characters of the input string in ascending lexicographical order. Sorting ensures that characters like 't', 'r', 'y', 'g', 'u', 'b' are grouped together in a way that breaks the required subsequence pattern.

Algorithms/Techniques:
- Sorting the string to rearrange characters in lexicographical order
- Time Complexity: O(n log n) per test case, where n is the length of the string
- Space Complexity: O(1) additional space (excluding input/output), as sorting is done in-place

Time Complexity: O(n log n) per test case
Space Complexity: O(1) additional space
*/
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string a;
    std::cin >> a;
    sort(a.begin(), a.end()); // Sort the characters of the string in ascending order
    std::cout << a << std::endl; // Output the sorted string
  }
}


// https://github.com/VaHiX/CodeForces/