// Problem: CF 1759 A - Yes-Yes?
// https://codeforces.com/contest/1759/problem/A

/*
 * Problem: A. Yes-Yes?
 * Purpose: Determine if a given string is a substring of an infinite repetition of "Yes".
 * Algorithm:
 *   - For each test case, check if the input string appears as a substring in the pattern "YesYesYes...".
 *   - The key idea is to cycle through all possible rotations of "Yes" (since it's a 3-character string).
 *   - If the first character of input matches any rotation of "Yes", we compute the shift and verify
 *     that the entire input string matches the pattern with that rotation applied.
 *
 * Time Complexity: O(t * n), where t is number of test cases, and n is average length of input strings.
 * Space Complexity: O(1) additional space (excluding input/output storage).
 */

#include <iostream>
#include <string>
int main() {
  const std::string pat = "Yes"; // The base pattern to match against
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    int shift(0);
    for (long p = 0; p < pat.size(); p++) { // Try each rotation of "Yes" as a potential start
      if (pat[p] == s[0]) {
        shift = p; // Record the shift needed to align first char
        break;
      }
    }
    bool ans(true);
    for (long p = 0; ans && p < s.size(); p++) { // Validate the full match with computed shift
      if (s[p] != pat[(p + shift) % 3]) { // Check character-by-character using modular arithmetic
        ans = false;
      }
    }
    std::cout << (ans ? "YES" : "NO") << std::endl; // Output result for current test case
  }
}


// https://github.com/VaHiX/codeForces/