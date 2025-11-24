// Problem: CF 1862 A - Gift Carpet
// https://codeforces.com/contest/1862/problem/A

/*
A. Gift Carpet
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given a grid of n rows and m columns of lowercase Latin letters, determine if it's possible to form the word "vika" by selecting exactly one letter from each of four consecutive columns (from left to right), such that the selected letters spell "v", "i", "k", "a" in order.

Algorithm:
- For each test case, iterate through all columns from left to right.
- For each column, search for the next required character from the string "vika".
- If we find a matching letter in a column, increment our index in the target string.
- After processing all columns, if we have matched all characters of "vika", output "YES", otherwise "NO".

Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for storing the grid

Techniques:
- Greedy matching of characters column by column from left to right.
- Early termination on successful match.

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string tgt = "vika"; // Target string to match
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> v(n); // Grid of characters
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    long idx(0); // Index in target string "vika"
    for (long col = 0; col < m; col++) {
      for (long row = 0; row < n; row++) {
        if (v[row][col] == tgt[idx]) { // Check if character matches current target
          ++idx; // Move to next required character
          break; // Move to next column after finding a match
        }
      }
    }
    std::cout << (idx >= tgt.size() ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/