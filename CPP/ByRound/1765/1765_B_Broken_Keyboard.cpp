// Problem: CF 1765 B - Broken Keyboard
// https://codeforces.com/contest/1765/problem/B

/*
B. Broken Keyboard

Algorithm: Simulation
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1)

The problem simulates a malfunctioning keyboard where every other key press
results in two characters being printed instead of one. The pattern is:
- 1st, 3rd, 5th, ... presses: print 1 character
- 2nd, 4th, 6th, ... presses: print 2 characters

We simulate the process by iterating through the string and checking if it could
have been produced by such a keyboard behavior. The algorithm alternates between
expecting 1 or 2 characters from the input string, based on the current step.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long idx(0), mod(0);       // idx: current position in string, mod: toggle for 1/2 char rule
    bool ans(true);
    while (idx < n) {
      if (mod) {               // If expecting 2 characters
        if (idx + 1 >= n || s[idx + 1] != s[idx]) {  // Check if next char matches current
          ans = false;
          break;
        }
        idx += 2;              // Move by 2 positions as we consumed 2 chars
      } else {                 // If expecting 1 character
        ++idx;                 // Move by 1 position
      }
      mod = 1 - mod;           // Toggle between 0 and 1 (1 means expect 2 chars next)
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/