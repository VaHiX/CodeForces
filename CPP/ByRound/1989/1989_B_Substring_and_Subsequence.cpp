// Problem: CF 1989 B - Substring and Subsequence
// https://codeforces.com/contest/1989/problem/B

/*
B. Substring and Subsequence
time limit per test2 seconds
memory limit per test256 megabytes

Problem Description:
Given two strings a and b, find the minimum length of a string that contains a as a substring and b as a subsequence.

Algorithm:
- For each possible starting position in string b where the subsequence matching can begin,
  we calculate how many characters are needed from a and b to form such a valid string.
- We iterate over all possible overlaps between the beginning of b and a, and compute
  the minimal total length needed.

Time Complexity: O(|a| * |b|^2)
Space Complexity: O(1)

Techniques:
- Greedy substring-subsequence matching
- Brute-force enumeration of starting positions in b
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string a;
    std::cin >> a;
    std::string b;
    std::cin >> b;
    long cnt(a.size() + b.size()); // Initialize with maximum possible length
    for (long start = 0; start < b.size(); start++) { // Try each starting index in b
      long idx = start; // Index in b to match against a
      for (int p = 0; p < a.size(); p++) { // Iterate through each character of a
        if (idx < b.size() && a[p] == b[idx]) { // Match found, move index in b
          ++idx;
        }
      }
      long total = a.size() + start + (b.size() - idx); // Calculate total length for current overlap
      cnt = (cnt < total ? cnt : total); // Keep minimum
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/