// Problem: CF 1829 C - Mr. Perfectly Fine
// https://codeforces.com/contest/1829/problem/C

/*
 * Problem: C. Mr. Perfectly Fine
 *
 * Purpose:
 *   Given n books, each with a time cost and a binary string indicating which skills are acquired,
 *   find the minimum time to acquire both required skills (skills 1 and 2).
 *
 * Algorithm:
 *   - For each book, categorize it based on the binary skill string:
 *     "00": contributes nothing useful
 *     "01": contributes skill 2 only
 *     "10": contributes skill 1 only
 *     "11": contributes both skills
 *   - Track minimum time for books that give only skill 1 ("10") and skill 2 ("01").
 *   - Also track minimum time for books that give both skills ("11").
 *   - The result is either:
 *     - Minimum time of a "11" book (if any)
 *     - Sum of the cheapest "10" and "01" books
 *     - If neither is possible, return -1.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 */

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false); // Optimize I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    long res(-1), a(-1), b(-1); // res: min time for "11", a: min time for "10", b: min time for "01"
    for (long p = 0; p < n; p++) {
      long m;
      std::string w;
      std::cin >> m >> w;
      if (w == "10") { // Only skill 1
        if (a < 0) {
          a = m;
        } else {
          a = (a < m ? a : m); // Keep the minimum time for skill 1 only books
        }
      } else if (w == "01") { // Only skill 2
        if (b < 0) {
          b = m;
        } else {
          b = (b < m ? b : m); // Keep the minimum time for skill 2 only books
        }
      } else if (w == "11") { // Both skills
        if (res < 0) {
          res = m;
        } else {
          res = (res < m ? res : m); // Keep the minimum time for both skills books
        }
      }
    }
    long sum = (a > 0 && b > 0) ? (a + b) : -1; // Sum of best "10" and "01" if both exist
    if (res < 0 && sum > 0) {
      res = sum; // If no "11" book exists, use the pair of "10" and "01"
    } else if (sum > 0) {
      res = (res < sum ? res : sum); // Compare "11" with the pair
    }
    std::cout << res << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/