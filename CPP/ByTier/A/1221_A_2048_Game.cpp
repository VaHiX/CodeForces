// Problem: CF 1221 A - 2048 Game
// https://codeforces.com/contest/1221/problem/A

/*
 * Problem: Determine if it's possible to obtain 2048 from a multiset of powers of two
 *          by repeatedly combining equal elements into their sum.
 *
 * Algorithm:
 * - For each query, count how many times each power of two appears (up to 2^11 = 2048).
 * - Simulate the merging process using a greedy approach:
 *   - Start with the smallest powers and merge them into larger ones.
 *   - Each step doubles the count of the next higher power.
 * - Check if we end up with at least one 2048 in our final counts.
 *
 * Time Complexity: O(n) per query, since we iterate through all elements once and
 *                  process a fixed number of bits (12).
 * Space Complexity: O(1), as we use only a fixed-size vector of size 12.
 */

#include <cstdio>
#include <vector>

int main() {
  const long D = 12;  // Number of powers of two to consider (from 2^0 to 2^11)
  long q;
  scanf("%ld", &q);
  while (q--) {
    std::vector<long> a(D, 0);  // Count of each power of two (0 to 11)
    long n;
    scanf("%ld", &n);
    while (n--) {
      long x;
      scanf("%ld", &x);
      // Count how many times each bit is set in x
      for (long p = 0; x && p < D; x /= 2, p++) {
        if (x == 1) {  // If the current bit is set to 1
          ++a[p];
        }
      }
    }
    // Merge from low bits to high bits (like a carry propagation)
    for (long p = 1; p < D; p++) {
      a[p] += a[p - 1] / 2;
    }
    puts(a.back() ? "YES" : "NO");  // Check if we have at least one 2048
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/