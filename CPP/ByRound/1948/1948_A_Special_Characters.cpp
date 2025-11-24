// Problem: CF 1948 A - Special Characters
// https://codeforces.com/contest/1948/problem/A

/*
 * Code Purpose:
 *   This program determines whether it's possible to construct a string of uppercase Latin letters 
 *   such that there are exactly n special characters. A character is special if it equals at least 
 *   one of its neighbors. The solution uses a simple construction approach leveraging the fact 
 *   that two consecutive identical characters contribute 2 special characters (the first and last 
 *   of the pair when extended). If n is odd, it's impossible to form such a string.
 *
 * Algorithms/Techniques:
 *   - Greedy construction using pairs of same characters ("AA" or "BB")
 *   - Observing that each pair contributes exactly 2 special characters
 *   - Special handling for odd n (impossible case)
 *
 * Time Complexity: O(n) per test case, since we output n characters total.
 * Space Complexity: O(1) additional space (excluding output string).
 */

#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    if (n % 2) { // If n is odd, it's impossible to have exactly n special characters
      std::cout << "NO" << std::endl;
      continue;
    }
    std::cout << "YES" << std::endl;
    for (long p = 0; 2 * p < n; p++) {
      // Alternate between "AA" and "BB" to build the string 
      // Each pair contributes 2 special characters
      std::cout << ((p % 2) ? "AA" : "BB");
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/