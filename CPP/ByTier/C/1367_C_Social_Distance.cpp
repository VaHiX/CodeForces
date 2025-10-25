// Problem: CF 1367 C - Social Distance
// https://codeforces.com/contest/1367/problem/C

/*
C. Social Distance
Time complexity: O(n) per test case
Space complexity: O(1) excluding input string

Algorithms/Techniques: Two-pass greedy approach
- First pass from left to right to mark zeros that can be converted to ones,
  considering the rightmost occupied table within k distance.
- Second pass from right to left to count how many zeros can be safely converted
  without violating the social distance constraint.

The algorithm ensures that for each new "1" placed, it respects the minimum distance k
from previously placed "1"s by maintaining a boundary of forbidden positions.

*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    long last(-k - 7); // Initialize to a value that ensures first '1' is processed correctly
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == '1') {
        last = p; // Update the position of the last occupied table
      } else if (p <= last + k) {
        s[p] = '2'; // Mark as temporarily occupied to avoid conflicts in second pass
      }
    }
    long cnt(0);
    last = s.size() + k + 7; // Initialize to a value beyond string length
    for (long p = s.size(); p >= 0; p--) {
      if (s[p] == '1') {
        last = p; // Update the position of the last occupied table
      } else if (p + k < last && s[p] == '0') {
        ++cnt;           // Increment count for valid new occupation
        last = p;        // Update last occupied position to current one
      }
    }
    std::cout << cnt << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/