// Problem: CF 1760 B - Atilla's Favorite Problem
// https://codeforces.com/contest/1760/problem/B

#include <iostream>
#include <string>

int main() {
  long t;                    // Number of test cases
  std::cin >> t;
  while (t--) {
    long n;                  // Length of the string
    std::cin >> n;
    std::string s;           // Input string
    std::cin >> s;
    long mx(0);              // Variable to store maximum character value (0-25 for a-z)
    for (long p = 0; p < n; p++) {
      long x = s[p] - 'a';   // Convert character to index (a=0, b=1, ..., z=25)
      mx = (mx > x) ? mx : x; // Update maximum index
    }
    std::cout << (mx + 1) << std::endl; // Output alphabet size required (add 1 since indices start at 0)
  }
}
/*
Flowerbox:
Problem: B. Atilla's Favorite Problem

Purpose:
This code determines the minimum alphabet size required to write a given string. 
For each test case, it identifies the highest character in the string (as an index from 0 to 25) and adds 1 to get the required alphabet size.

Algorithms/Techniques:
- Single pass through the string
- Character-to-index conversion using ASCII values
- Linear scan for maximum value

Time Complexity: O(n), where n is the length of the input string, as we iterate through each character once.
Space Complexity: O(1), since only a constant amount of extra space is used regardless of input size.
*/

// https://github.com/VaHiX/codeForces/