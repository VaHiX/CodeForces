// Problem: CF 1944 A - Destroying Bridges
// https://codeforces.com/contest/1944/problem/A

/*
 * Problem: Destroying Bridges
 * Algorithm/Technique: Greedy, Graph Theory
 *
 * Description:
 * Given n islands and initially all pairs of islands connected by a bridge,
 * we are to determine the minimum number of reachable islands from island 1
 * after optimally destroying at most k bridges.
 *
 * Key Insight:
 * - If k is large enough (k >= n*(n-1)/2), all bridges are destroyed, so only island 1 is reachable.
 * - Otherwise, we aim to isolate as many islands as possible by removing bridges,
 *   maximizing the number of disjoint components that do not include island 1.
 *
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // If k is large enough to destroy all bridges, only island 1 is reachable
    // Otherwise, even if we remove k bridges optimally, at least n islands are reachable
    printf("%ld\n", k >= n - 1 ? 1 : n);
  }
}


// https://github.com/VaHiX/codeForces/