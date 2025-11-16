// Problem: CF 1744 C - Traffic Light
// https://codeforces.com/contest/1744/problem/C

/*
C. Traffic Light
Problem: Given a cyclic traffic light pattern (string of r, y, g), determine the minimum time to guarantee crossing 
         the road when the current color is known. Green ('g') allows immediate crossing.

Algorithm:
- For each test case:
  1. If current color is 'g', output 0 (already green).
  2. Otherwise, for each occurrence of 'g' in the string:
     - Compute distance to next 'g' in the cyclic pattern.
     - Track maximum such distance among all 'g's encountered.
- Approach: Two-pass algorithm over the string using a sliding window technique.
  First pass: Find first 'g' after current position.
  Second pass: From end to start, track distances from each color to next 'g'.

Time Complexity: O(n) per test case. Linear scan required for all positions.
Space Complexity: O(1) excluding input string. Constant extra space used.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    char c;
    std::cin >> n >> c;
    std::string s;
    std::cin >> s;
    if (c == 'g') {
      std::cout << "0" << std::endl;
      continue;
    }
    long nxt(0);
    // Find first 'g' after current position to initialize nxt
    for (long p = 0; (!nxt) && p < s.size(); p++) {
      if (s[p] == 'g') {
        nxt = n + p;  // Add n to handle cyclic behavior
        break;
      }
    }
    long res(0);
    // Traverse from end of string backwards to compute max wait time
    for (long p = n - 1; p >= 0; p--) {
      if (s[p] == 'g') {
        nxt = p;  // Update next green position
      } else if (s[p] == c) {
        long cur = nxt - p;           // Distance from current color to next green
        res = (res > cur) ? res : cur; // Keep maximum wait time
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/