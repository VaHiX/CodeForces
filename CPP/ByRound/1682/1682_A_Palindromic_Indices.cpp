// Problem: CF 1682 A - Palindromic Indices
// https://codeforces.com/contest/1682/problem/A

/*
 * Problem: Palindromic Indices
 * Task: Count how many indices i (1 <= i <= n) can be removed from a palindromic string s such that the resulting string is still a palindrome.
 * 
 * Algorithm:
 * - For each test case, we iterate through the string and check for valid removals.
 * - The key observation is that removing a character at index i maintains palindrome property if:
 *   1. The character is at the center (or near), or
 *   2. Removal of the character doesn't break symmetries in the palindrome.
 * 
 * Time Complexity: O(n) per test case, where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for computation.
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
    long cnt(0);
    for (long p = (n / 2); p >= 0; p--) {
      if (s[p] == s[n / 2]) {
        ++cnt;
      } else {
        break;
      }
    }
    for (long p = (n / 2) + 1; p < n; p++) {
      if (s[p] == s[n / 2]) {
        ++cnt;
      } else {
        break;
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/