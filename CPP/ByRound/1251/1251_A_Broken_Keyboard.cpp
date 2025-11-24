// Problem: CF 1251 A - Broken Keyboard
// https://codeforces.com/contest/1251/problem/A

/*
Problem: A. Broken Keyboard
Purpose: Given a string representing the output of a keyboard with some malfunctioning buttons, 
         determine which characters correspond to buttons that work correctly.

Algorithm:
  - For each character in the string, we group consecutive identical characters.
  - If a group has an odd number of characters, it indicates a correct button press.
    Otherwise, if even, it could be from a malfunctioning button (which prints two chars).
  - We track which characters have odd-length groups and output those in alphabetical order.

Time Complexity: O(N) where N is the total length of all strings in input
Space Complexity: O(1) since we use fixed size vector of 26 elements

Input format:
  First line: number of test cases t
  Each test case: a string s (1 <= len(s) <= 500)

Output format:
  For each test case, print characters that definitely work correctly in alphabetical order.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const long N = 26;
  long q;
  std::cin >> q;
  while (q--) {
    std::string s;
    std::cin >> s;
    std::vector<int> w(N, 0); // Track which characters work correctly
    long cnt(1); // Counter for consecutive same characters
    for (long p = 1; p < s.size(); p++) {
      if (s[p] == s[p - 1]) {
        ++cnt;
      } else {
        w[s[p - 1] - 'a'] |= (cnt % 2); // If count is odd, button worked
        cnt = 1;
      }
    }
    w[s.back() - 'a'] |= (cnt % 2); // Handle last group
    for (long p = 0; p < N; p++) {
      if (w[p]) {
        std::cout << (char)('a' + p);
      }
    }
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/