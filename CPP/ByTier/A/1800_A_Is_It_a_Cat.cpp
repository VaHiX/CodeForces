// Problem: CF 1800 A - Is It a Cat?
// https://codeforces.com/contest/1800/problem/A

/*
 * Problem: A. Is It a Cat?
 * Purpose: Determine if a given string represents a valid cat meowing pattern.
 *          A valid pattern consists of sequences of 'm'/'M', 'e'/'E', 'o'/'O', 'w'/'W'
 *          in that order, with each sequence being non-empty.
 *
 * Algorithms/Techniques:
 *   - Linear scan with state tracking
 *   - Case-insensitive character matching
 *   - Sequential validation of pattern segments
 *
 * Time Complexity: O(n) where n is the length of the input string (per test case)
 * Space Complexity: O(1) excluding input storage
 */

#include <iostream>
#include <string>
int main() {
  const std::string cs = "meow"; // Target sequence to match
  long t;
  std::cin >> t;
  while (t--) { // Process each test case
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long idx(0); // Current position in the target sequence "meow"
    bool iscat(s[0] == 'm' || s[0] == 'M'); // Check if first char is 'm' or 'M'
    for (long p = 0; iscat && p < s.size(); p++) {
      if ('A' <= s[p] && s[p] <= 'Z') { // Convert uppercase to lowercase
        s[p] += ('a' - 'A');
      }
      if (s[p] == cs[idx]) { // Current character matches expected one
        continue;
      } else if ((idx + 1 < cs.size()) && s[p] == cs[idx + 1]) { // Move to next expected char
        ++idx;
      } else { // Invalid character - pattern broken
        iscat = false;
      }
    }
    iscat = iscat && (idx == 3); // Ensure we've reached end of "meow"
    std::cout << (iscat ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/