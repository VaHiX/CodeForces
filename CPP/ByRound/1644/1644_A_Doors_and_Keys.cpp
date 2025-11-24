// Problem: CF 1644 A - Doors and Keys
// https://codeforces.com/contest/1644/problem/A

/*
 * Problem: Doors and Keys
 * Purpose: Determine if a knight can open all doors in a hallway given the order of doors and keys.
 * Algorithm: 
 *   - Iterate through the string from left to right.
 *   - Keep track of collected keys (r, g, b).
 *   - When encountering a door:
 *     - If it's a uppercase letter (door), check if corresponding key has been collected.
 *     - If not, return "NO".
 *   - If all doors are successfully opened, return "YES".
 *
 * Time Complexity: O(n) where n is the length of the string (6 characters).
 * Space Complexity: O(1) as we use a constant amount of extra space.
 */

#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    bool res(true); // Assume the knight can proceed
    bool r(0), g(0), b(0); // Track if keys are collected
    for (size_t p = 0; p < s.size(); p++) {
      if (s[p] == 'r') {
        r = true; // Collect red key
      } else if (s[p] == 'g') {
        g = true; // Collect green key
      } else if (s[p] == 'b') {
        b = true; // Collect blue key
      } else if (s[p] == 'R' && !r) {
        res = false; // Can't open red door without red key
      } else if (s[p] == 'B' && !b) {
        res = false; // Can't open blue door without blue key
      } else if (s[p] == 'G' && !g) {
        res = false; // Can't open green door without green key
      }
    }
    std::cout << (res ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/