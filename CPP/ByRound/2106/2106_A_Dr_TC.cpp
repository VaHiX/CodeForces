// Problem: CF 2106 A - Dr. TC
// https://codeforces.com/contest/2106/problem/A

/*
 * Problem: Dr. TC's Binary String Grid
 *
 * Purpose:
 *   This program calculates the total number of '1' bits in a grid formed by
 *   flipping each bit of a given binary string 's' in turn to create n different strings,
 *   and summing all '1' bits across these strings.
 *
 * Algorithm:
 *   - For each test case:
 *     - Read the length n and binary string s.
 *     - For each character in s:
 *       - If it's '1', it contributes (n - 2) + 1 = n - 1 ones to the total
 *         (because in the original string, it's 1; in all other strings, it flips to 0).
 *       - If it's '0', it contributes 1 one to the total (it becomes 1 in only one row).
 *     - Sum up contributions for all characters.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input space
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Synchronize C++ iostream with C stdio for faster input/output
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n; // Read length of binary string
    std::string s;
    std::cin >> s; // Read the binary string
    long cnt(0); // Initialize counter for total number of 1s
    for (size_t p = 0; p < s.size(); p++) {
      cnt += (n - 2) * (s[p] == '1') + 1; // Count contributions from each bit
    }
    printf("%ld\n", cnt); // Print result
  }
}


// https://github.com/VaHiX/codeForces/