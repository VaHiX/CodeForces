// Problem: CF 1666 D - Deletive Editing
// https://codeforces.com/contest/1666/problem/D

/*
 * Problem: Deletive Editing
 * Algorithm: Two-pointer technique with character frequency tracking.
 *
 * Approach:
 * - We simulate the reverse process of deleting characters from 'from' to obtain 'to'.
 * - We iterate backwards through both strings, checking if the current character in 'from'
 *   matches the one in 'to'. If it does and we haven't already used a character with that value,
 *   we move the pointer for 'to' backward.
 * - If the characters do not match, we mark the character from 'from' as used to track
 *   which ones have been "deleted".
 * - At the end, if all of 'to' has been matched, then it's possible to form 'to' from 'from'.
 *
 * Time Complexity: O(n * m), where n is the length of string 'from', and m is the length of string 'to'.
 * Space Complexity: O(1) - constant space (only 26-element vector used for tracking).
 */
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    std::string from;
    std::cin >> from;
    std::string to;
    std::cin >> to;
    std::vector<bool> f(26, 0); // Tracks whether a character has been used
    long idx(to.size() - 1);    // Pointer for 'to'
    bool possible(true);
    for (long p = from.size() - 1; possible && idx >= 0 && p >= 0; p--) {
      if (from[p] == to[idx]) {        // Characters match
        if (!f[from[p] - 'A']) {       // If this character hasn't been used yet
          --idx;                       // Move to next required character in 'to'
        } else {
          possible = false;            // Already used, so not valid
        }
      } else {
        f[from[p] - 'A'] = 1;           // Mark the character as used
      }
    }
    possible = possible && (idx < 0);  // Ensure we've matched all of 'to'
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/