// Problem: CF 2044 B - Normal Problem
// https://codeforces.com/contest/2044/problem/B

/*
 * Problem: B. Normal Problem
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(n) due to string storage and manipulation
 *
 * Algorithm/Techniques:
 * - Reverse the input string
 * - Swap 'p' with 'q' and vice versa
 * - Output the transformed string
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::reverse(s.begin(), s.end());  // Reverse the string in-place
    for (size_t p = 0; p < s.size(); p++) {
      if (s[p] == 'p') {               // If character is 'p', replace with 'q'
        s[p] = 'q';
      } else if (s[p] == 'q') {        // If character is 'q', replace with 'p'
        s[p] = 'p';
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/