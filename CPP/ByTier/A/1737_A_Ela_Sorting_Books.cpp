// Problem: CF 1737 A - Ela Sorting Books
// https://codeforces.com/contest/1737/problem/A

/*
 * Problem: A. Ela Sorting Books
 * Purpose: Given a string of lowercase letters representing book titles,
 *          split them into k compartments of n/k books each, compute the MEX
 *          for each compartment, and form a result string. Find the lexicographically
 *          greatest possible such string.
 *
 * Algorithm:
 *   - For each compartment, we want to maximize the MEX letter.
 *   - We iterate through letters from 'a' to 'y'.
 *   - For each letter, calculate how many books of that type are available.
 *   - Distribute books to compartments greedily to maximize MEX for each.
 *   - The strategy is to fill the result string with characters that indicate
 *     the lexicographically greatest possible outcome based on MEX computations.
 *
 * Time Complexity: O(n * k) per test case, since we process up to n characters and up to k compartments.
 * Space Complexity: O(1) excluding input/output (fixed-size frequency array of size 26).
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;
    std::vector<long> f(26, 0); // Frequency array for letters 'a' to 'y'
    for (long p = 0; p < s.size(); p++) {
      ++f[s[p] - 'a']; // Count frequency of each letter
    }
    long idx(k); // Initialize index tracker
    std::string res(k, 'a'); // Result string initialized with 'a's
    for (long p = 0; idx >= 0 && p < (n / k) && p < 26; p++) {
      char x = (p + 'a'); // Current letter being considered
      idx = (idx < f[p] ? idx : f[p]); // Determine how many of this letter we can use
      char y = x + 1; // Next letter after current one
      for (long u = 0; u < idx; u++) {
        res[u] = y; // Fill result with next letter to maximize MEX
      }
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/