// Problem: CF 1243 B1 - Character Swap (Easy Version)
// https://codeforces.com/contest/1243/problem/B1

/*
 * Problem: B1. Character Swap (Easy Version)
 * Purpose: Determine if two strings can be made equal by performing exactly one swap between characters of the two strings.
 *
 * Algorithms/Techniques:
 * - String comparison and character tracking.
 * - Greedy approach to detect possible swaps.
 *
 * Time Complexity: O(N) where N is the length of the strings.
 * Space Complexity: O(1) since we use a fixed-size vector of size 26 (for lowercase letters).
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long N = 26;  // Number of lowercase English letters
  long q;
  std::cin >> q;
  while (q--) {
    long n;
    std::cin >> n;
    std::string s, t;
    std::cin >> s >> t;
    long diff(0);  // Tracks number of differing positions: 0 = all same, 1 = one pair differs, 2 = can make equal with swap
    char x, y;     // Stores characters from first differing position in s and t
    std::vector<long> v(N, 0);  // Count occurrences of matching characters at same positions
    for (long p = 0; p < n; p++) {
      if (s[p] == t[p]) {
        ++v[s[p] - 'a'];  // Increment count for character at same position
      } else if (diff == 0) {
        x = s[p];         // Store character from s at first differing position
        y = t[p];         // Store character from t at first differing position
        diff = 1;         // Mark that we found one differing position
      } else if (diff == 1) {
        if (s[p] == x && t[p] == y) {
          diff = 2;       // If matching pair of characters can make strings equal with one swap
        } else {
          diff = -1;      // Invalid case: different pairs, cannot resolve with one swap
          break;
        }
      } else {
        diff = -1;        // More than 2 differences, impossible to fix with one swap
        break;
      }
    }
    if (diff == 0) {
      // All characters match, check if any character appears at least twice in matching positions.
      // This would allow a valid swap without changing the rest of the string.
      for (long p = 0; p < N; p++) {
        if (v[p] >= 2) {
          diff = 2;
          break;
        }
      }
    }
    std::cout << (diff == 2 ? "Yes" : "No") << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/