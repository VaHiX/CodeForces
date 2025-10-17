// Problem: CF 1932 A - Thorns and Coins
// https://codeforces.com/contest/1932/problem/A

/*
Problem: A. Thorns and Coins
Description:
  Given a path of n cells, each cell can be empty ('.'), contain a coin ('@'), or have thorns ('*').
  You start at the first cell and can move 1 or 2 steps forward, as long as the destination is not a thorn.
  Collecting coins along the way is allowed. Find the maximum number of coins that can be collected.

Algorithms/Techniques:
  - Greedy approach with forward traversal
  - Linear scan through string to count coins while avoiding consecutive thorns

Time Complexity: O(n) where n is the length of the string, since we process each character once.
Space Complexity: O(1) as we only use a constant amount of extra space.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization between C and C++ standard streams for faster input/output
  long t; // Number of test cases
  std::cin >> t;
  while (t--) {
    long n; // Length of the path string
    std::cin >> n;
    std::string s; // Path string representation
    std::cin >> s;
    long cnt(0); // Counter for coins collected
    for (long p = 1; p < s.size(); p++) { // Start from second cell (index 1)
      if (s[p - 1] == '*' && s[p] == '*') { // If current and previous cells are both thorns, cannot proceed
        break;
      }
      cnt += (s[p] == '@'); // Add to counter if current cell has a coin
    }
    printf("%ld\n", cnt); // Output total coins collected
  }
}


// https://github.com/VaHiX/codeForces/