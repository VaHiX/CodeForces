// Problem: CF 1209 C - Paint the Digits
// https://codeforces.com/contest/1209/problem/C

/*
Algorithm: Brute-force with optimization
Approach:
- Try all possible values of x from '0' to '9' as a threshold.
- For each x, simulate painting digits:
  - If digit >= x, paint it with color 2.
  - Otherwise, paint it with color 1.
- Track the maximum digit seen so far for each color to ensure non-decreasing order.
- If valid assignment is found for any x, output it.

Time Complexity: O(10 * n) = O(n), where n is the length of input string.
Space Complexity: O(n) for storing the input and output strings.
*/

#include <iostream>
#include <string>

int main() {
  long q;
  std::cin >> q;
  while (q--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string ans;
    for (int x = '0'; x <= '9'; x++) {
      bool possible(true);
      std::string tmp(s);
      int a(-1), b(-1);
      for (long p = 0; p < s.size() && possible; p++) {
        // If current digit is greater than or equal to threshold x, assign color 2
        if (s[p] > x || (s[p] == x && b <= x)) {
          tmp[p] = '2';
          // Check if the sequence remains non-decreasing for color 2
          if (s[p] < b) {
            possible = false;
            break;
          }
          // Update maximum for color 2
          b = (b > s[p]) ? b : s[p];
        } else {
          // Assign color 1
          tmp[p] = '1';
          // Check if the sequence remains non-decreasing for color 1
          if (s[p] < a) {
            possible = false;
            break;
          }
          // Update maximum for color 1
          a = (a > s[p]) ? a : s[p];
        }
      }
      // If assignment works for current threshold x, use it
      if (possible) {
        ans = tmp;
        break;
      }
    }
    // Output result
    if (ans.size()) {
      std::cout << ans << std::endl;
    } else {
      std::cout << "-" << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/