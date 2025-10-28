// Problem: CF 1654 B - Prefix Removals
// https://codeforces.com/contest/1654/problem/B

/*
B. Prefix Removals
Algorithm: For each string, we repeatedly remove the longest prefix that also occurs elsewhere in the string.
Time Complexity: O(n) per test case, where n is the length of the string. Each character is processed at most twice (once in forward pass, once in backward pass).
Space Complexity: O(1) as we use a fixed-size vector of 26 elements for tracking characters.

Techniques:
- Two-pointer approach with backward iteration
- Boolean vector to track seen characters
- String substring operation to extract result
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    std::vector<bool> v(26, 0); // Track which characters have been seen
    long idx(s.size());         // Initialize index to end of string
    for (long p = s.size() - 1; p >= 0; p--) { // Traverse from right to left
      if (v[s[p] - 'a']) {       // If character was already seen
        continue;                // Skip this position
      }
      idx = p;                   // Update index to current position
      v[s[p] - 'a'] = 1;         // Mark character as seen
    }
    std::cout << s.substr(idx) << std::endl; // Output substring from idx to end
  }
}


// https://github.com/VaHiX/codeForces/