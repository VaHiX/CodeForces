// Problem: CF 2114 A - Square Year
// https://codeforces.com/contest/2114/problem/A

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Convert the 4-digit string into a single number
    long y = 1000 * (s[0] - '0') + 100 * (s[1] - '0') + 10 * (s[2] - '0') +
             (s[3] - '0');
    long a(-1);
    // Iterate through possible values of p to find if y is a perfect square
    for (long p = 0; p * p <= y; p++) {
      if (p * p == y) {
        a = p;
        break;
      }
    }
    // Output result: if a is found, output it with 0; otherwise output -1
    std::cout << a << (a >= 0 ? " 0" : "") << std::endl;
  }
}
/*
 * Problem: A. Square Year
 *
 * Purpose:
 *   Given a 4-digit year string s, determine whether it can be expressed as
 *   (a + b)^2 where a and b are non-negative integers such that the concatenation
 *   of a and b forms the digits of s.
 *
 * Algorithm:
 *   - Parse input string to form integer y (the square value we're looking for).
 *   - Iterate through all possible square roots p from 0 up to sqrt(y),
 *     checking if p^2 == y.
 *   - If found, output p and 0 (representing a = p, b = 0). Else, output -1.
 *
 * Time Complexity: O(sqrt(Y)), where Y is the maximum value of y (i.e., 9999),
 *   so effectively constant time.
 *
 * Space Complexity: O(1), only using fixed extra space.
 */

// https://github.com/VaHiX/codeForces/