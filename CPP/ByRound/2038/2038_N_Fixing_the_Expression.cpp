// Problem: CF 2038 N - Fixing the Expression
// https://codeforces.com/contest/2038/problem/N

/*
 * Problem: N. Fixing the Expression
 * 
 * Purpose: Given a 3-character string representing a comparison expression 
 *          (e.g., "3<7"), modify the comparison operator to make the expression true.
 *          The first and last characters are digits, and the middle is a comparison symbol.
 * 
 * Algorithm:
 *   - Read the input expression.
 *   - Compare the first and third characters (the digits).
 *   - Change the middle character (comparison operator) to match the actual relationship
 *     between the two digits.
 * 
 * Time Complexity: O(1) - Fixed number of operations per test case.
 * Space Complexity: O(1) - Only using fixed size variables, no extra space needed.
 */

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    // Compare the first and third characters (digits)
    if (s[0] < s[2]) {
      s[1] = '<';  // If first digit is less than third, use '<'
    } else if (s[0] > s[2]) {
      s[1] = '>';  // If first digit is greater than third, use '>'
    } else if (s[0] == s[2]) {
      s[1] = '=';  // If first digit equals third, use '='
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/