// Problem: CF 2045 C - Saraga
// https://codeforces.com/contest/2045/problem/C

/*
C. Saraga
Problem Description:
Given two strings S and T, find the shortest "interesting" abbreviation that can be formed by taking a prefix of S and a suffix of T such that there are at least two distinct ways to split this abbreviation into the prefix of S and suffix of T.

Approach:
- Preprocess string S to store for each character the earliest index where it appears (from left).
- Traverse string T from right to left.
- For each character in T, if it exists in S, compute the minimal length of abbreviation formed by combining:
    - prefix of S up to the index of that character
    - suffix of T starting from current position
- Keep track of the minimum length abbreviation found.

Time Complexity: O(|S| + |T|)
Space Complexity: O(1) for auxiliary array (fixed size 26), O(|S| + |T|) for input strings.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::string s, t;
  std::cin >> s >> t;
  long v[26] = {0}; // Array to store first occurrence of each character in S
  for (long p = 1; p < s.size(); p++) { // Start from 1 because we need at least one char for prefix
    if (v[s[p] - 'a'] > 0) {
      continue; // Skip if already processed
    }
    v[s[p] - 'a'] = p; // Store the first appearance index of character
  }
  std::string res("-1"); // Initialize result to -1 (impossible case)
  bool found(false); // Flag to track if any valid abbreviation was found
  for (long p = t.size() - 2; p >= 0; p--) { // Start from second last index of T
    if (v[t[p] - 'a'] <= 0) {
      continue; // Skip if character not in S
    }
    long tstlen = v[t[p] - 'a'] + t.size() - p; // Length of the combined prefix+suffix
    if (!found || tstlen < res.size()) { // Update result if shorter or first found
      found = true;
      res = s.substr(0, v[t[p] - 'a']) + t.substr(p); // Construct abbreviation
    }
  }
  std::cout << res << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/