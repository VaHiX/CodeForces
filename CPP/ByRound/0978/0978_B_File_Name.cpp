// Problem: CF 978 B - File Name
// https://codeforces.com/contest/978/problem/B

/*
 * Problem: File Name
 * Purpose: Determine the minimum number of characters to remove from a string 
 *          so that it does not contain "xxx" as a substring.
 * 
 * Algorithm:
 * - Traverse the string and keep track of consecutive 'x' characters.
 * - When we encounter an 'x', we increment a counter.
 * - If the counter reaches 2 (meaning we have seen 3 'x's in a row), 
 *   we increment the removal counter and reset the 'x' counter.
 * - If we encounter a non-'x' character, we reset the 'x' counter.
 * 
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) - only using a few variables regardless of input size.
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long cnt(0), rem(0);
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == 'x') {
      if (cnt >= 2) {    // If we already have 2 x's, this third one needs to be removed
        ++rem;
      } else {
        ++cnt;           // Count consecutive x's
      }
    } else {
      cnt = 0;           // Reset counter when a non-x character is encountered
    }
  }
  std::cout << rem << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/