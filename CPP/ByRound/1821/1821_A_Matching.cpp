// Problem: CF 1821 A - Matching
// https://codeforces.com/contest/1821/problem/A

/*
 * Problem: Count the number of positive integers that match a given template.
 * A template consists of digits (0-9) and/or question marks ('?').
 * A positive integer matches the template if it's possible to replace each '?'
 * with a digit such that the resulting number is valid (no leading zeros).
 *
 * Algorithm:
 * - For each test case, process the string from left to right.
 * - The first character has special rules:
 *   - If it's '0', then the result is 0 (as leading zero is invalid for positive numbers).
 *   - If it's '?', it can be any of 1-9 (9 choices), so start with res = 9.
 * - For remaining characters:
 *   - If it's '?', there are 10 possible digits (0-9).
 *   - If it's a digit, there is only 1 choice.
 * - Multiply all possibilities together to get total count.
 *
 * Time Complexity: O(n) per test case where n is the length of the template string.
 * Space Complexity: O(1) - constant extra space used.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long res(1);
    if (s[0] == '?') {
      res = 9; // First digit cannot be 0 for positive number, so 9 choices
    } else if (s[0] == '0') {
      res = 0; // If first digit is 0, invalid for positive number
    }
    for (long p = 1; p < s.size(); p++) {
      res *= (s[p] == '?') ? 10 : 1; // For each '?' we have 10 choices, for a digit we have 1 choice
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/