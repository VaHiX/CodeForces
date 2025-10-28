// Problem: CF 1363 B - Subsequence Hate
// https://codeforces.com/contest/1363/problem/B

/*
B. Subsequence Hate
Algorithm: Dynamic Programming with Prefix Sums
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(n) for storing prefix sums

The problem asks to find the minimum number of flips to make a binary string "good",
where a good string does not contain "010" or "101" as a subsequence.
The approach uses prefix counts of '0's and '1's and evaluates all possible transitions
between different patterns (all 0s, all 1s, or patterns avoiding forbidden subsequences).

Key idea:
- For each position, compute how many 0s and 1s are there up to that point.
- Evaluate two cases for minimum flips:
  1. Convert entire string to all 0s or all 1s.
  2. Try to make string such that it avoids the forbidden patterns by checking 
     combinations of prefix 1s and suffix 0s (and vice versa), and compute minimal flips needed.

*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<long> a(s.size(), 0), z(s.size(), 0);
    // a[p] stores count of '1's from 0 to p
    // z[p] stores count of '0's from 0 to p
    for (long p = 0; p < s.size(); p++) {
      z[p] = (p ? z[p - 1] : 0) + (s[p] == '0');
      a[p] = (p ? a[p - 1] : 0) + (s[p] == '1');
    }
    long tz(z.back()), ta(a.back()); // Total counts of 0s and 1s
    long res(ta < tz ? ta : tz); // Initialize with minimum flips to make all 0 or all 1
    
    for (long p = 0; p < s.size(); p++) {
      // x: flips needed if we want all 0s up to p and all 1s after p
      // y: flips needed if we want all 1s up to p and all 0s after p
      long x = a[p] + (tz - z[p]);
      long y = z[p] + (ta - a[p]);
      res = res < x ? res : x;
      res = res < y ? res : y;
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/