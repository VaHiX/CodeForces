// Problem: CF 2093 B - Expensive Number
// https://codeforces.com/contest/2093/problem/B

/*
B. Expensive Number

Purpose:
This program determines the minimum number of digits to remove from a given number such that the cost (number divided by sum of its digits) is minimized.
The key insight is that removing digits strategically can reduce the cost effectively.

Algorithm:
1. For each test case, we process the string representation of the number.
2. We count transitions from '1' to '0' and vice versa to determine regions.
3. The idea is to identify how many zeros can be grouped together, as moving a zero to the rightmost position increases the sum of digits but decreases the ratio.
4. By computing prefix counts of zeros and updating count of 1's after each zero transition, we can compute an efficient solution.

Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(1), constant extra space (ignoring input storage).

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Disable synchronization for faster I/O
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cz(0), z(0); // cz stores cumulative count of zeros seen so far, z counts current consecutive zeros
    for (long p = 0; p < s.size(); p++) { // Traverse the string character by character
      if (s[p] == '0') {
        ++z; // Increment zero counter when a '0' is encountered
      } else {
        cz += z; // Add current zeros to cumulative count when a non-zero digit is found
        z = 0;   // Reset zero counter
      }
    }
    long ans = s.size() - cz - 1; // Calculate minimum digits to remove
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/