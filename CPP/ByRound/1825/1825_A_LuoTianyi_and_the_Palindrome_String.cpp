// Problem: CF 1825 A - LuoTianyi and the Palindrome String
// https://codeforces.com/contest/1825/problem/A

/*
 * Problem: LuoTianyi and the Palindrome String
 * Task: Given a palindrome string s, find the length of the longest non-empty subsequence 
 *       which is not a palindrome. If no such subsequence exists, return -1.
 *
 * Algorithm:
 *   - If all characters in the string are the same (e.g., "aaa"), then every subsequence
 *     will also be a palindrome, so return -1.
 *   - Otherwise, we can construct a non-palindromic subsequence by removing one character,
 *     and the result will have length (n - 1).
 *
 * Time Complexity: O(n) where n is the length of the string
 * Space Complexity: O(1)
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
    bool same(true); // flag to check if all characters are the same
    long res(s.size() - 1); // default answer is length of string minus one
    for (long p = 1; same && p < s.size(); p++) {
      if (s[p] != s[0]) { // if any character differs from the first
        same = false;
      }
    }
    if (same) {
      res = -1; // all characters are the same, so no non-palindrome subsequence exists
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/