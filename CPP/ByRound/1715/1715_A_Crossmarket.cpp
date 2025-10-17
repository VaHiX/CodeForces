// Problem: CF 1715 A - Crossmarket
// https://codeforces.com/contest/1715/problem/A

/*
 * Problem: Crossmarket
 * Purpose: Calculate minimum total energy for Stanley and Megan to travel
 *          from their start positions to end positions in an n x m grid,
 *          where portals allow teleportation between cells with portals.
 *
 * Algorithms/Techniques:
 *   - Greedy approach to minimize path lengths by using portal teleportation
 *   - Mathematical formula to compute optimal energy usage
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long mn = (m > n) ? m : n;  // Find maximum of n and m
    long ans = (m + n > 2) ? (2 * (m + n - 1) - mn) : 0;  // Compute minimal energy
    printf("%ld\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/