// Problem: CF 1676 A - Lucky?
// https://codeforces.com/contest/1676/problem/A

/*
 * Problem: A. Lucky?
 * Purpose: Determine if a 6-digit ticket is lucky by checking if the sum of the first three digits 
 *          equals the sum of the last three digits.
 * Algorithms/Techniques: Simple digit manipulation and summation.
 * Time Complexity: O(t * n), where t is the number of test cases and n = 6 (constant).
 * Space Complexity: O(1) - only using a fixed amount of extra space.
 */
#include <iostream>
#include <string>
int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long t(0); // Variable to store the difference between sums
    for (long p = 0; p < 6; p++) {
      // For first 3 digits, subtract their value; for last 3, add their value
      t += (p < 3 ? -1 : 1) * (s[p] - '0');
    }
    std::cout << (t ? "NO" : "YES") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/