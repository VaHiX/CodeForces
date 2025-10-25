// Problem: CF 1469 A - Regular Bracket Sequence
// https://codeforces.com/contest/1469/problem/A

#include <stdio.h>
#include <iostream>
#include <string>

/*
 * Problem: Determine if a bracket sequence with '?' can be made into a valid RBS
 * Algorithm: Simple greedy check
 * Time Complexity: O(n) where n is the length of string s
 * Space Complexity: O(1) - only using constant extra space
 *
 * Key observations:
 * 1. First character cannot be ')' (no opening bracket to match)
 * 2. Last character cannot be '(' (no closing bracket to match)
 * 3. Total length must be even (each '(' needs a matching ')')
 * 
 * The solution checks these three conditions.
 */

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Check if first char is ')' or last char is '(' or length is odd
    puts((s[0] == ')' || s[s.size() - 1] == '(' || s.size() % 2) ? "NO"
                                                                 : "YES");
  }
}

// https://github.com/VaHiX/codeForces/