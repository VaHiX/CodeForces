// Problem: CF 1311 C - Perform the Combo
// https://codeforces.com/contest/1311/problem/C

/*
 * Problem: C. Perform the Combo
 * Purpose: Calculate how many times each letter (a-z) is pressed during a sequence of tries
 *          to perform a combo string. Each try may fail at a specific position, causing
 *          the combo to restart.
 *
 * Algorithms/Techniques:
 *   - Prefix sum technique with difference array for efficient updates
 *   - Reverse pass to compute times each character contributes
 *   - Counting frequencies of characters in the final press sequence
 *
 * Time Complexity: O(n + m) per test case
 * Space Complexity: O(n + 26) = O(n) for vectors and counters
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  const long N = 26; // Number of lowercase letters
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    
    // v[x-1] tracks how many times we start over at position x-1 (0-indexed)
    std::vector<long> v(s.size(), 0);
    for (long p = 0; p < m; p++) {
      long x;
      std::cin >> x;
      ++v[x - 1]; // Increment the count where mistake occurs (convert to 0-based index)
    }

    // times[p] stores how many times s[p] is pressed
    std::vector<long> times(s.size(), 0);
    times[s.size() - 1] = 1; // Last character is always pressed once in final try
    
    // Build prefix sum from right to left
    for (long p = s.size() - 2; p >= 0; p--) {
      times[p] = times[p + 1] + v[p]; // Each position gets contributions from future positions and itself
    }
    
    // Count final occurrences of each character
    std::vector<long> cnt(N, 0); // Track counts for letters a to z
    for (long p = 0; p < s.size(); p++) {
      cnt[s[p] - 'a'] += times[p]; // Accumulate press counts based on how many times each char is pressed
    }
    
    // Output counts for all 26 letters
    for (long p = 0; p < N; p++) {
      std::cout << cnt[p] << " ";
    };
    std::cout << std::endl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/