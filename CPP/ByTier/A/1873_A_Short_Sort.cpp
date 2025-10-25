// Problem: CF 1873 A - Short Sort
// https://codeforces.com/contest/1873/problem/A

/*
Problem: A. Short Sort
Task: Determine if three cards 'a', 'b', 'c' can be arranged in order "abc" with at most one swap.

Algorithms/Techniques: 
  - Direct comparison of input string with target string "abc"
  - Brute-force check for all possible swaps (at most one swap allowed)

Time Complexity: O(1) - Fixed number of operations (3 characters, at most 1 swap)
Space Complexity: O(1) - Only using a fixed amount of extra space (string of size 3)

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization between C and C++ standard streams for faster input/output
  int t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the current test case string
    // Check if the string is already "abc" or one of the two invalid cases "bca" or "cab"
    // If it is either of those, we cannot make it "abc" with at most one swap
    std::cout << ((s == "bca" || s == "cab") ? "NO" : "YES") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/