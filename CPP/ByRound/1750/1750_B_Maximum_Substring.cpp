// Problem: CF 1750 B - Maximum Substring
// https://codeforces.com/contest/1750/problem/B

/*
B. Maximum Substring
Algorithm: Sliding window / linear scan with tracking of max lengths of consecutive 0s and 1s
Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a few variables for counting

A binary string is a string consisting only of the characters 0 and 1. You are given a binary string s.
For some non-empty substring t of string s containing x characters 0 and y characters 1, define its cost
as:
x * y, if x > 0 and y > 0;
x^2, if x > 0 and y = 0;
y^2, if x = 0 and y > 0.

Given a binary string s of length n, find the maximum cost across all its non-empty substrings.
*/
#include <stdio.h>
#include <iostream>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    // cn: count of 1s in current consecutive sequence of 1s
    // cz: count of 0s in current consecutive sequence of 0s
    // ln: max length of consecutive 1s so far
    // lz: max length of consecutive 0s so far
    // bn: current length of consecutive 1s
    // bz: current length of consecutive 0s
    ll cn(0), cz(0), ln(0), lz(0), bn(0), bz(0);
    for (ll p = 0; p < s.size(); p++) {
      int x = (s[p] - '0');
      if (x == 0) {
        // Reset current count of 1s, increment count of 0s
        bn = 0;
        ++cz;
        ++bz;
        // Update maximum length of consecutive 0s
        lz = (lz > bz) ? lz : bz;
      }
      if (x == 1) {
        // Reset current count of 0s, increment count of 1s
        bz = 0;
        ++cn;
        ++bn;
        // Update maximum length of consecutive 1s
        ln = (ln > bn) ? ln : bn;
      }
    }
    // Compute maximum cost from three possible cases:
    // Case 1: max consecutive 0s * max consecutive 1s (when both > 0)
    // Case 2: max consecutive 0s squared (when no 1s in the substring)
    // Case 3: max consecutive 1s squared (when no 0s in the substring)
    ll res = lz * lz;
    res = (res > ln * ln) ? res : (ln * ln);
    res = (res > cz * cn) ? res : (cz * cn);
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/