// Problem: CF 1037 C - Equalize
// https://codeforces.com/contest/1037/problem/C

/*
C. Equalize
Purpose: Given two binary strings a and b of same length, find minimum cost to make a equal to b using two operations:
         1. Swap any two bits with cost |i-j|
         2. Flip any bit with cost 1
Algorithms/Techniques: Greedy approach with careful handling of adjacent mismatches.
Time Complexity: O(n) - single pass through the strings
Space Complexity: O(1) - only using a few variables, no extra space needed

Input:
- First line: n (length of strings)
- Second line: string a
- Third line: string b

Output: Minimum cost to make a equal to b
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::string a, b;
  std::cin >> a >> b;
  long cnt(0);
  for (long p = 0; p < n; p++) {
    // If bits at position p are already equal, skip
    if (a[p] == b[p]) {
      continue;
    } 
    // If current and next positions have different bits, and swapping them is beneficial
    // Check if we can swap two adjacent mismatches to fix both at once
    else if (a[p] != b[p] && p + 1 < n && a[p + 1] != b[p + 1] &&
             a[p] != a[p + 1]) {
      ++cnt;
      a[p] = b[p];              // Update a[p] to match b[p]
      a[p + 1] = b[p + 1];      // Update a[p+1] to match b[p+1]
    } else {
      ++cnt;
      a[p] = b[p];              // Flip bit at p (cost 1)
    }
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/