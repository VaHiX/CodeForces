// Problem: CF 1108 C - Nice Garland
// https://codeforces.com/contest/1108/problem/C

/*
Code Purpose:
This code solves the problem of making a garland "nice" by recoloring the minimum number of lamps. 
A garland is considered nice if all lamps of the same color have indices with distances divisible by 3.
The solution tries 6 possible repeating patterns of length 3 (since only 3 colors and each color must repeat every 3 positions), 
and chooses the pattern requiring the least number of recolors.

Algorithms/Techniques:
- Brute-force generation of 6 possible repeating color patterns for a 3-length cycle.
- For each pattern, count how many lamps need to be recolored.
- Output the pattern with minimum recolors and the resulting garland.

Time Complexity: O(n), where n is the number of lamps.
Space Complexity: O(1), as we use a fixed-size array of 6 patterns and a few variables.
*/

#include <iostream>
#include <string>

int main() {
  const int N = 6;
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  // Predefined 6 repeating patterns of length 3 (BGR, BRG, GBR, GRB, RBG, RGB)
  std::string f[N] = {"BGR", "BRG", "GBR", "GRB", "RBG", "RGB"};
  long mn(s.size() + 1);  // Initialize with a value larger than possible
  std::string pattern = "";  // To store the best pattern found
  for (long p = 0; p < 6; p++) {
    std::string cur = f[p];  // Current pattern being tested
    long cnt(0);
    for (long q = 0; q < s.size(); q++) {
      // Count mismatches between current lamp and expected color in pattern
      cnt += (s[q] != cur[q % 3]);
    }
    if (cnt < mn) {
      mn = cnt;  // Update minimum recolors needed
      pattern = cur;  // Store the pattern that yields minimum recolors
    }
  }
  std::cout << mn << std::endl;  // Print minimum number of recolors
  for (long p = 0; p < s.size(); p++) {
    std::cout << pattern[p % 3];  // Reconstruct garland using the optimal pattern
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/