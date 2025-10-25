// Problem: CF 1404 A - Balanced Bitstring
// https://codeforces.com/contest/1404/problem/A

/*
 * Problem: Balanced Bitstring
 * Algorithm/Technique: Greedy with modular indexing and validation
 *
 * Time Complexity: O(n) per test case, where n is the length of the string s.
 * Space Complexity: O(k), due to storing a temporary string t of size k.
 *
 * Approach:
 * - For each position i in the input string s, we determine which character
 *   should be placed at position (i % k) in a candidate k-length pattern string t.
 * - If two characters at different positions but same modulo index are conflicting,
 *   it's impossible to form a valid k-balanced string.
 * - After processing all known characters, check if the frequency of '0' and '1'
 *   in the pattern t is within limits (each <= k/2) for a valid k-balanced string.
 */

#include <iostream>
#include <string>

using namespace std;

bool solve() {
  int n, k, c0 = 0, c1 = 0;
  string s;
  cin >> n >> k >> s;
  string t(k, '?'); // Initialize pattern string of size k with '?'

  for (int i = 0; i < n; i++) {
    if (s[i] != '?') { // Only process non '?' characters
      if (t[i % k] == '?')
        t[i % k] = s[i]; // Assign character to pattern position if not set
      else if (t[i % k] != s[i])
        return 0; // Conflict found: cannot form valid string
      t[i % k] = s[i]; // Ensure it's assigned (this line redundant but safe)
    }
  }

  // Count occurrences of '0' and '1' in the pattern string t
  for (int i = 0; i < k; i++) {
    if (t[i] == '1')
      c1++;
    if (t[i] == '0')
      c0++;
  }

  // Check if counts of '0' and '1' are within allowed limits (k/2 each)
  return c0 <= k / 2 && c1 <= k / 2;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    cout << (solve() ? "YES\n" : "NO\n");
  return 0;
}


// https://github.com/VaHiX/codeForces/