// Problem: CF 1791 B - Following Directions
// https://codeforces.com/contest/1791/problem/B

/*
B. Following Directions

Algorithm: Simulation
- For each test case, simulate Alperen's movement along the string.
- Track current position (x, y) starting at (0, 0).
- At each step, update x or y based on the move:
    'L' -> x--
    'R' -> x++
    'U' -> y++
    'D' -> y--
- Check if at any point (x, y) equals (1, 1), which means he passes the candy.
- Output "YES" if candy is passed during traversal; otherwise "NO".

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) excluding input storage.

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long x(0), y(0);  // Current position, starting at origin (0, 0)
    bool candy(false);  // Flag to indicate if candy at (1, 1) is ever passed
    for (long p = 0; p < s.size(); p++) {
      if (s[p] == 'L') {
        --x;
      } else if (s[p] == 'R') {
        ++x;
      } else if (s[p] == 'U') {
        ++y;
      } else if (s[p] == 'D') {
        --y;
      }
      if (x == 1 && y == 1) {  // Check if we reach the candy position
        candy = true;
      }
    }
    std::cout << (candy ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/