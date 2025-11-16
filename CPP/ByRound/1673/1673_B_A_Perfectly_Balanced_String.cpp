// Problem: CF 1673 B - A Perfectly Balanced String?
// https://codeforces.com/contest/1673/problem/B

/*
 * Problem: B. A Perfectly Balanced String?
 *
 * Purpose:
 *   Determine whether a given string is "perfectly balanced".
 *   A string is perfectly balanced if for all substrings and all pairs of characters,
 *   the absolute difference between their frequencies in that substring is at most 1.
 *
 * Algorithm:
 *   - For each test case, count unique characters in the string.
 *   - If there's only one unique character, return "YES".
 *   - Otherwise, check if the string can be partitioned such that
 *     each character appears in a repeating pattern where all characters
 *     have frequencies differing by at most 1 in every substring.
 *     This is checked by verifying that for some period k (number of unique chars),
 *     and all positions p >= k, s[p-k] == s[p].
 *
 * Time Complexity: O(n) where n is the length of the string.
 * Space Complexity: O(1) since there are at most 26 unique lowercase letters.
 */

#include <iostream>
#include <set>
#include <stdio.h>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the string
    std::set<long> cs; // Set to store unique characters
    for (long p = 0; p < s.size(); p++) {
      cs.insert(s[p]); // Insert each character into set to count unique ones
    }
    const long k = cs.size(); // Number of unique characters
    bool res(true); // Flag to track if string is perfectly balanced

    // Check periodicity condition for perfectly balanced strings
    for (long p = k; res && p < s.size(); p++) {
      if (s[p - k] != s[p]) { // If pattern breaks, it's not perfectly balanced
        res = false;
      }
    }
    puts(res ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/