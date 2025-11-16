// Problem: CF 1389 C - Good String
// https://codeforces.com/contest/1389/problem/C

/*
C. Good String
Purpose: Given a string of digits 0-9, find the minimum number of characters to erase to make the string "good".
A string is good if its left cyclic shift equals its right cyclic shift.
Algorithm:
  - For each pair of digits (a,b), simulate a pattern where we alternate between a and b.
  - Count how many characters we can keep in such an alternating pattern.
  - The answer for each test case is the total length minus the maximum count found.

Time Complexity: O(100 * n) = O(n), where n is the length of the string.
Space Complexity: O(1) (excluding input storage)

Techniques:
  - Brute-force over all possible alternating digit pairs (0-9).
  - Simulate greedy pattern matching for each pair.
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
    long mx(0);
    for (int a = 0; a <= 9; a++) {
      for (int b = 0; b <= 9; b++) {
        bool state(0); // flag to track whether we expect 'a' or 'b'
        long cnt(0);   // count of characters matched in current pattern
        for (long p = 0; p < s.size(); p++) {
          if (state && s[p] == ('0' + a)) { // If expecting 'a' and found it
            ++cnt;
            state = 1 - state; // switch expectation to 'b'
          } else if (!state && s[p] == ('0' + b)) { // If expecting 'b' and found it
            ++cnt;
            state = 1 - state; // switch expectation to 'a'
          }
        }
        // Adjust count for cases where we have an extra character due to pattern mismatch
        cnt -= (a != b) && (cnt % 2);
        mx = (mx > cnt) ? mx : cnt; // update maximum
      }
    }
    std::cout << (s.size() - mx) << std::endl; // minimum characters to erase
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/