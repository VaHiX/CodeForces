// Problem: CF 1204 A - BowWow and the Timetable
// https://codeforces.com/contest/1204/problem/A

/*
 * Problem: BowWow and the Timetable
 * Purpose: Count how many trains have departed strictly before time 's'.
 *          Trains depart at times 4^k (1, 4, 16, 64, ...) in binary representation.
 * Algorithm:
 *   - Parse input binary string s
 *   - Check if s is exactly "0" or starts with '1' (special cases)
 *   - Verify all remaining digits are zero for the case where s = 2^k type numbers
 *   - Compute how many powers of 4 are less than s using bit manipulation and division
 * Time Complexity: O(n), where n is the length of string s (number of bits)
 * Space Complexity: O(1) - only using fixed extra variables
 */

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  bool z(s == "0" || s[0] == '1'); // z is true if s is 0 or starts with 1 (i.e., s = 1*2^k)
  for (long p = 1; p < s.size(); p++) {
    if (s[p] != '0') { // Check if there's a non-zero digit after first position
      z = 0;
      break;
    }
  }
  bool fw(z && s.size() % 2); // fw is true when z is true and number of bits is odd (special case for powers of 4)
  long cnt = (s.size() + 1 - z) / 2; // Compute result using formula derived from bit positions
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/