// Problem: CF 1671 A - String Building
// https://codeforces.com/contest/1671/problem/A

/*
 * Problem: Determine if a string can be built using only substrings "aa", "aaa", "bb", and "bbb".
 * Algorithm: 
 *   - For each character in the string, count consecutive identical characters.
 *   - If a group of consecutive characters has fewer than 2 characters, return "NO".
 *   - If all groups have at least 2 characters, return "YES".
 * Time Complexity: O(n), where n is the total length of input strings across all test cases.
 * Space Complexity: O(1), excluding input storage.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long cnt(0);
    bool ans(true);
    for (long p = 0; p < s.size(); p++) {
      ++cnt; // Increment counter for consecutive characters
      if (p + 1 >= s.size() || s[p + 1] != s[p]) {
        // If next character is different or end of string, check the group size
        if (cnt < 2) {
          ans = false;
          break;
        }
        cnt = 0; // Reset counter for next group
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/