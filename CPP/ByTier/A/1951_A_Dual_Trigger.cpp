// Problem: CF 1951 A - Dual Trigger
// https://codeforces.com/contest/1951/problem/A

/*
 * Problem: Determine if a binary string configuration of lamps can be achieved
 *          using operations where two non-adjacent off lamps are turned on.
 *
 * Algorithms/Techniques:
 *   - Dual Trigger (checking for adjacent '1's and count of '1's)
 *
 * Time Complexity: O(n) per test case, where n is the length of the string
 * Space Complexity: O(1), only using a few variables for counting and flags
 */

#include <stdio.h>
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
    long cnt(0);                // Count of '1's in the string
    bool adj(false);            // Flag to check if any two adjacent '1's exist
    for (long p = 0; p < n; p++) {
      cnt += (s[p] == '1');     // Increment count if current char is '1'
      if (p > 0 && s[p - 1] == '1' && s[p] == '1') {  // Check for adjacent '1's
        adj = true;
      }
    }
    if (cnt == 2 && adj) {      // Special case: exactly two '1's and they are adjacent
      puts("NO");
    } else {
      puts(cnt % 2 ? "NO" : "YES");  // If count is odd, impossible; else possible
    }
  }
}


// https://github.com/VaHiX/codeForces/