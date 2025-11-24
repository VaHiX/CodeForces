// Problem: CF 2050 C - Uninteresting Number
// https://codeforces.com/contest/2050/problem/C

/*
C. Uninteresting Number
Purpose: Determine if a number can be made divisible by 9 by squaring its digits (only if square < 10).
Algorithm:
- For each digit in the string representation of the number, compute:
    - Sum of digits modulo 9
    - Count of '2' and '3'
- Based on sum modulo 9, check specific conditions involving counts of 2s and 3s.
- If any condition is met, output "YES", otherwise "NO".

Time Complexity: O(n) where n is the total length of all input strings.
Space Complexity: O(1) (ignoring input storage).

Techniques:
- Modular arithmetic
- Greedy logic with digit counting
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string w;
    std::cin >> w;
    long d(0), r(0), s(0);
    for (long p = 0; p < w.size(); p++) {
      int x = (w[p] - '0');  // Convert character to digit
      s += x;                // Accumulate sum of digits
      d += (x == 2);         // Count of digit '2'
      r += (x == 3);         // Count of digit '3'
    }
    s %= 9;  // Sum modulo 9
    bool possible(false);
    if (!s) {
      possible = true;  // Already divisible by 9
    } else if (s == 1 && ((d > 3) || (d > 0 && r > 0))) {
      possible = true;  // Adjust for sum 1 case
    } else if (s == 2 &&
               ((d >= 8) || (d >= 5 && r >= 1) || (d >= 2 && r >= 2))) {
      possible = true;  // Adjust for sum 2 case
    } else if (s == 3 && ((d >= 3) || (r >= 1))) {
      possible = true;  // Adjust for sum 3 case
    } else if (s == 4 && (d >= 7 || (d >= 4 && r >= 1) || (d >= 1 && r >= 2))) {
      possible = true;  // Adjust for sum 4 case
    } else if (s == 5 && d >= 2) {
      possible = true;  // Adjust for sum 5 case
    } else if (s == 6 && (d >= 6 || (d >= 3 && r >= 1) || (r >= 2))) {
      possible = true;  // Adjust for sum 6 case
    } else if (s == 7 && d > 0) {
      possible = true;  // Adjust for sum 7 case
    } else if (s == 8 && (d >= 5 || (d >= 2 && r >= 1))) {
      possible = true;  // Adjust for sum 8 case
    } else {
      possible = false;
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/