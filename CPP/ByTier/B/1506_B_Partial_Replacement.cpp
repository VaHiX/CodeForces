// Problem: CF 1506 B - Partial Replacement
// https://codeforces.com/contest/1506/problem/B

/*
B. Partial Replacement
Algorithm: Greedy approach to place minimum number of 'x' characters such that:
- First '*' is replaced with 'x'
- Last '*' is replaced with 'x'
- Distance between adjacent 'x's does not exceed k

Time Complexity: O(n) per test case, where n is the length of string s
Space Complexity: O(1) - only using a few variables for tracking

*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long cnt(0), prev(-1), last(-1);
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '.') {   // Skip empty spots
        continue;
      }
      if (prev < 0) {      // First '*' found, place an 'x' here
        ++cnt;
        prev = p;
        continue;
      }
      if (p > prev + k) {  // Need to place another 'x' due to distance constraint
        ++cnt;
        prev = last;       // Move prev to the last placed 'x'
      }
      last = p;            // Update last '*' position
    }
    printf("%ld\n", cnt + (prev < last));  // Add one more if needed for final '*'
  }
}


// https://github.com/VaHiX/codeForces/