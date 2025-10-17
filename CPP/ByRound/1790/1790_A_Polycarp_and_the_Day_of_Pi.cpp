// Problem: CF 1790 A - Polycarp and the Day of Pi
// https://codeforces.com/contest/1790/problem/A

/*
 * Problem: A. Polycarp and the Day of Pi
 * Purpose: Check how many leading digits of a given string match the beginning of π.
 * Algorithm: Compare input string with precomputed value of π digit-by-digit.
 * Time Complexity: O(n), where n is the length of the input string (up to 30).
 * Space Complexity: O(1), since we use constant extra space (fixed π string size).
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const std::string pi = "31415926535897932384626433832795028841971693993751058"
                         "209749445923078164062862089986280348253421170679";
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string x;
    std::cin >> x; // Read the input string representing digits of π
    long cnt(0);   // Counter for matching digits
    for (long p = 0; p < x.size(); p++) {
      if (x[p] == pi[p]) { // If current digit matches π's digit
        ++cnt;
      } else {
        break; // Stop when mismatch occurs
      }
    }
    std::cout << cnt << std::endl; // Output the count of matching leading digits
  }
}


// https://github.com/VaHiX/codeForces/