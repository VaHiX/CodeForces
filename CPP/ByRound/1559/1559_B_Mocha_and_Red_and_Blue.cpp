// Problem: CF 1559 B - Mocha and Red and Blue
// https://codeforces.com/contest/1559/problem/B

/*
Algorithm: Greedy approach to minimize imperfectness by filling '?' characters
           such that no two adjacent squares have the same color.
           The strategy is to:
           1. Find the first non-'?' character from the left.
           2. Fill all '?' characters to the left of this first character,
              alternating colors.
           3. Fill all '?' characters to the right of this first character,
              also alternating colors based on the previous character.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(1) excluding the input/output storage.
*/

#include <iostream>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long idx(0);
    // Find the first non-'?' character from the left
    while (idx < n && s[idx] == '?') {
      ++idx;
    }
    // If all characters are '?', set the last one to 'B'
    if (idx == n) {
      s[--idx] = 'B';
    }
    // Fill '?' characters to the left of idx
    for (long p = idx - 1; p >= 0; p--) {
      if (s[p] == '?') {
        s[p] = (s[p + 1] == 'B') ? 'R' : 'B';
      }
    }
    // Fill '?' characters to the right of idx
    for (long p = idx + 1; p < n; p++) {
      if (s[p] == '?') {
        s[p] = (s[p - 1] == 'B') ? 'R' : 'B';
      }
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/