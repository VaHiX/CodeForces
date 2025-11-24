// Problem: CF 1146 A - Love "A"
// https://codeforces.com/contest/1146/problem/A

/*
 * Problem: A. Love "A"
 * Purpose: Find the longest "good" string that can be formed by erasing some characters from input string s,
 *          where a "good" string has more than half of its characters as 'a'.
 *
 * Algorithm:
 * 1. Count total number of 'a's in the string.
 * 2. Compute minimum required length for a good string: 2 * count_a - 1.
 * 3. Return the smaller of (string length) and (minimum required length).
 *
 * Time Complexity: O(n), where n is the size of the input string.
 * Space Complexity: O(1), only using a few variables regardless of input size.
 */

#include <iostream>
#include <string>

int main() {
  std::string s;
  std::cin >> s;
  long cnt(0); // Count of 'a' characters
  for (long p = 0; p < s.size(); p++) {
    cnt += (s[p] == 'a'); // Increment count if current character is 'a'
  }
  long ans(2 * cnt - 1); // Minimum length needed to make string good
  ans = (s.size() < ans) ? s.size() : ans; // Ensure result doesn't exceed original string length
  std::cout << ans << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/