// Problem: CF 1995 D - Cases
// https://codeforces.com/contest/1995/problem/D

/*
D. Cases
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: Sliding window technique combined with bitmask dynamic programming.
- Use sliding window to process all substrings of length k in text.
- For each substring, we track which letters appear in it using a bitmask.
- We maintain a boolean array `m` whose element at index `mask` indicates whether
  such a mask (set of present letters) can occur as a suffix in some valid word.
- After processing all windows, we eliminate impossible masks by checking if any
  subset of a mask implies that the mask itself is invalid (due to case contradiction).
- Finally, compute minimum number of cases by selecting the smallest set of bits
  (cases) such that all possible masks are compatible with this selection.

Time complexity: O(n * c + 2^c * c)
Space complexity: O(2^c + n)

*/

#include <algorithm>
#include <iostream>
bool m[300001];
char s[300001];
int main() {
  std::cin.tie(0)->sync_with_stdio(0);
  int t;
  std::cin >> t;
  while (t--) {
    int n, c, k;
    std::cin >> n >> c >> k >> s; // Read input parameters and string
    for (int i = 1; i < 1 << c; i++)
      m[i] = 1;  // Initialize all non-zero masks to true (potential valid cases)
    int u[18]{}, v = 0;  // u: frequency of each letter in current window, v: bitmask of letters present
    for (int i = 0; i < k; i++)
      u[s[i] - 'A']++, v |= 1 << s[i] - 'A';  // Initialize first window
    for (int i = 0; i < n; i++) {
      m[(1 << c) - 1 ^ v] = 0, // Mark the complement of current mask as invalid (no case ending with these letters)
      v ^= (!--u[s[i] - 'A']) << s[i] - 'A'; // Remove the leftmost character from window
      if (i + k < n)
        u[s[i + k] - 'A']++, v |= 1 << s[i + k] - 'A'; // Add new rightmost character to window
    }
    for (int i = 0; i < c; i++)          // Propagate mask information: if a subset is valid, so is the superset
      for (int j = 0; j < 1 << c; j++)
        if (j & 1 << i)
          m[j ^ 1 << i] &= m[j];
    int ans = c;
    for (int i = 0; i < 1 << c; i++)
      if (m[i])
        ans = std::min(ans, __builtin_popcount(i)); // Find minimal number of set bits (minimum cases)
    std::cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/