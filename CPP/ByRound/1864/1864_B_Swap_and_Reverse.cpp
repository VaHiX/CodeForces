// Problem: CF 1864 B - Swap and Reverse
// https://codeforces.com/contest/1864/problem/B

/*
B. Swap and Reverse
Problem Description:
Given a string s of length n and an integer k, we can perform two types of operations:
1. Swap characters at positions i and i+2 (for valid i).
2. Reverse a substring of length k starting at position i.

Goal: Find the lexicographically smallest string achievable using these operations.

Algorithms/Techniques:
- If k is even: we can rearrange all characters freely due to ability to swap any two characters via multiple swaps.
- If k is odd: only characters at even indices can be arranged among themselves, and same for odd indices.
  We sort each group separately then interleave the results.

Time Complexity: O(n * log(n)) per test case (due to sorting)
Space Complexity: O(n) for temporary strings used during processing
*/

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    if (k % 2 == 0) {
      // If k is even, all characters can be rearranged freely
      sort(s.begin(), s.end());
      std::cout << s << std::endl;
      continue;
    } else {
      // If k is odd, separate even and odd indexed characters
      std::string odds(""), evens("");
      for (long p = 0; p < s.size(); p++) {
        if (p % 2) {
          odds += s[p];  // Collect characters at odd indices
        } else {
          evens += s[p]; // Collect characters at even indices
        }
      }
      sort(evens.begin(), evens.end());   // Sort even indexed characters
      sort(odds.begin(), odds.end());     // Sort odd indexed characters
      std::string res;
      for (long p = 0; p < n; p++) {
        if (p % 2) {
          res += odds[p / 2];   // Take from sorted odds
        } else {
          res += evens[p / 2];  // Take from sorted evens
        }
      }
      std::cout << res << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/