// Problem: CF 1509 B - TMT Document
// https://codeforces.com/contest/1509/problem/B

/*
 * Problem: B. TMT Document
 *
 * Purpose:
 *   Determines if a given string consisting of 'T' and 'M' characters can be partitioned
 *   into disjoint subsequences, each of which is exactly "TMT".
 *
 * Algorithm:
 *   1. Check if the total length is divisible by 3 (necessary condition).
 *   2. First pass from left to right:
 *      - Count 'T' and 'M' characters.
 *      - At any point, ensure that number of 'T's seen so far >= number of 'M's.
 *      - Verify that total count of 'T's = 2 * count of 'M's.
 *   3. Second pass from right to left:
 *      - Same validation as above to ensure backward consistency.
 *   4. If both passes succeed and the counts are correct, output "YES", otherwise "NO".
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for counting and flags.
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
    
    // Check if length is divisible by 3, required for valid partitioning
    bool possible(s.size() % 3 == 0);
    
    long tc(0), mc(0); // tc: T count, mc: M count
    
    // First pass from left to right:
    // Ensure at every point, number of T's >= number of M's
    for (long p = 0; p < s.size() && possible; p++) {
      if (s[p] == 'T') {
        ++tc;
      } else if (s[p] == 'M') {
        ++mc;
        if (tc < mc) { // Invalid sequence: more M's than T's so far
          possible = false;
          break;
        }
      }
    }
    
    // Check final counts:
    // Number of T's must be exactly twice the number of M's
    if (tc != 2 * mc) {
      possible = false;
    }
    
    tc = mc = 0; // Reset counters
    
    // Second pass from right to left:
    // Mirror validation for backward consistency
    for (long p = s.size() - 1; p >= 0 && possible; p--) {
      if (s[p] == 'T') {
        ++tc;
      } else if (s[p] == 'M') {
        ++mc;
        if (tc < mc) { // Invalid sequence: more M's than T's on backward scan
          possible = false;
          break;
        }
      }
    }
    
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/