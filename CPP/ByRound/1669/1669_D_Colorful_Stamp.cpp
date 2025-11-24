// Problem: CF 1669 D - Colorful Stamp
// https://codeforces.com/contest/1669/problem/D

/*
 * Problem: D. Colorful Stamp
 * 
 * Purpose: Determine if a given string of cells (containing 'W', 'R', 'B') can be formed using
 *          a stamp that applies two adjacent cells as 'R' and 'B' in either order.
 * 
 * Algorithm:
 *   - For each test case, iterate through the string character by character.
 *   - Track whether we have seen a 'R' or 'B' so far (red/blue flags).
 *   - When encountering a 'W', check if we've seen either 'R' or 'B' but not both — this would be invalid.
 *     Reset flags after encountering 'W'.
 *   - For 'R' and 'B', set corresponding flag.
 *   - After processing all characters, check if one of red/blue was set without the other — invalid.
 * 
 * Time Complexity: O(n) where n is the length of string s. Each character is visited once.
 * Space Complexity: O(1) excluding input storage. Only a few variables are used.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    bool red(0), blue(0), res(true);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'W') { // When we encounter a white cell, check previous red/blue state
        if (red ^ blue) { // If only one of red/blue was seen before this W, it's invalid
          res = false;
        }
        red = 0; // Reset flags
        blue = 0;
      } else if (s[p] == 'R') {
        red = true; // Mark that we've seen an R
      } else if (s[p] == 'B') {
        blue = true; // Mark that we've seen a B
      }
    }
    if (red ^ blue) { // After processing, if only one flag is set, it's invalid
      res = false;
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/