// Problem: CF 1689 A - Lex String
// https://codeforces.com/contest/1689/problem/A

/*
 * Problem: Lex String
 * Algorithm/Technique: Greedy approach with character selection based on
 *                      lexicographical ordering and k-constraint rules.
 * 
 * Time Complexity: O(n log n + m log m + n + m) per test case due to sorting
 *                  and single pass through strings.
 * Space Complexity: O(n + m) for storing the strings a and b.
 *
 * Approach:
 * 1. Sort both input strings a and b to get the lexicographically smallest
 *    characters at the front.
 * 2. Use two pointers (idxa, idxb) and counters (cnta, cntb) to track current
 *    position and consecutive count of operations for each string.
 * 3. At each step, greedily choose the smaller character from a[idxa] or b[idxb],
 *    respecting the max k consecutive operations limit.
 * 4. Append the chosen character to result string c and update counters.
 * 5. Continue until one of the strings is exhausted.
 */

#include <algorithm>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m, k;
    std::cin >> n >> m >> k;
    std::string a, b;
    std::cin >> a >> b;
    sort(a.begin(), a.end());  // Sort string a to get lexicographically smallest chars first
    sort(b.begin(), b.end());  // Sort string b to get lexicographically smallest chars first
    std::string c;
    long idxa(0), idxb(0), cnta(0), cntb(0);  // Pointers and counters for a and b
    while (idxa < a.size() && idxb < b.size()) {
      // If we've used k characters from b OR a's current char is smaller and we can take more from a
      if ((cntb >= k) || (a[idxa] < b[idxb] && cnta < k)) {
        c += a[idxa];  // Add character from a
        ++idxa;
        ++cnta;  // Increment count for a
        cntb = 0;  // Reset count for b
      } else if ((cnta >= k) || (b[idxb] < a[idxa] && cntb < k)) {
        c += b[idxb];  // Add character from b
        ++idxb;
        ++cntb;  // Increment count for b
        cnta = 0;  // Reset count for a
      }
    }
    std::cout << c << std::endl;
  }
}


// https://github.com/VaHiX/CodeForces/