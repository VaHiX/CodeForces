// Problem: CF 2036 C - Anya and 1100
// https://codeforces.com/contest/2036/problem/C

/*
 * Problem: Anya and 1100
 * Purpose: Determine if the substring "1100" exists in a binary string after performing updates.
 *
 * Algorithm:
 * - For each query, we update a character in the string.
 * - We maintain a count of how many times "1100" appears as a substring.
 * - To efficiently check and update, we use a sliding window approach around each position.
 * - The `check` function checks if "1100" starts at a given index.
 * - The `scount` function counts occurrences of "1100" around a position by checking a window of size 7.
 * - For each update, we recalculate the affected count using `scount`.
 *
 * Time Complexity: O(|s| + q * |s|) — for each query, we scan a fixed-size window (~7 positions).
 * Space Complexity: O(|s|) — to store the input string.
 */

#include <iostream>
#include <string>

bool check(std::string &s, long idx) {
  if (idx < 0) { // Invalid index
    return false;
  }
  if (idx + 3 >= s.size()) { // Not enough characters left for "1100"
    return false;
  }
  if (s[idx] == '1' && s[idx + 1] == '1' && s[idx + 2] == '0' &&
      s[idx + 3] == '0') {
    return true; // Found "1100"
  }
  return false;
}

long scount(std::string &s, long idx) {
  long total(0);
  for (long p = -3; p <= 3; p++) { // Check a window of size 7 around idx
    total += check(s, idx + p);
  }
  return total;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    std::string s;
    std::cin >> s;
    long q;
    std::cin >> q;
    long cnt(0);
    for (long p = 0; p < s.size(); p++) { // Count initial "1100" occurrences
      cnt += check(s, p);
    }
    while (q--) {
      long pos, b;
      std::cin >> pos >> b;
      cnt -= scount(s, pos - 1);       // Remove old contributions to count
      s[pos - 1] = ('0' + b);          // Update character
      cnt += scount(s, pos - 1);       // Add new contributions to count
      std::cout << (cnt ? "YES" : "NO") << std::endl; // Output result
    }
  }
}


// https://github.com/VaHiX/codeForces/