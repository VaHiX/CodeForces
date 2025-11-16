// Problem: CF 1506 C - Double-ended Strings
// https://codeforces.com/contest/1506/problem/C

/*
C. Double-ended Strings
Algorithm: 
    - For each pair of strings a and b, we compute the maximum length of a common substring starting at some position in a and some position in b.
    - Then, the minimum operations needed to make both strings equal is:
      (length of a + length of b - 2 * max_common_length)
Time Complexity: O(n^3) where n is the length of the longer string.
Space Complexity: O(1) excluding input storage.

The algorithm checks all possible substrings of a and b to find the longest common prefix that can be removed from both strings to make them equal.
*/
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string a, b;
    std::cin >> a >> b;
    long mx(0);
    for (long p = 0; p < a.size(); p++) {         // Start of substring in a
      for (long q = 0; q < b.size(); q++) {       // Start of substring in b
        for (long r = 0; p + r < a.size() && q + r < b.size(); r++) {
          if (a[p + r] == b[q + r]) {
            mx = (mx > r + 1) ? mx : (r + 1);   // Update maximum common length
          } else {
            break;                              // Stop when mismatch occurs
          }
        }
      }
    }
    long ans = a.size() + b.size() - 2 * mx;      // Minimum operations to make strings equal
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/