// Problem: CF 1837 B - Comparison String
// https://codeforces.com/contest/1837/problem/B

/*
 * Problem: B. Comparison String
 * Algorithm: Greedy approach to find minimum cost of array compatible with string s.
 *            The idea is to track the maximum consecutive same characters in the string,
 *            which corresponds to the maximum depth of a "chain" in the comparison graph.
 *            The result is this maximum depth + 1 (minimum number of distinct values needed).
 *
 * Time Complexity: O(n) per test case, where n is the length of the string s.
 * Space Complexity: O(1) additional space excluding input storage.
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
    long cnt(1), cur(1);
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == s[p - 1]) {
        ++cur;  // Continue the current sequence
      } else {
        cur = 1;  // Reset the counter when character changes
      }
      cnt = (cnt > cur) ? cnt : cur;  // Keep track of maximum consecutive count
    }
    printf("%ld\n", cnt + 1);  // Minimum cost is max consecutive + 1
  }
}


// https://github.com/VaHiX/codeForces/