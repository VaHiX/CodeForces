// Problem: CF 1802 B - Settlement of Guinea Pigs
// https://codeforces.com/contest/1802/problem/B

/*
 * Problem: B. Settlement of Guinea Pigs
 *
 * Purpose:
 *   Determine the minimum number of aviaries needed to ensure that at no point
 *   in time two guinea pigs of different genders live together, regardless of
 *   their actual genders.
 *
 * Algorithm:
 *   - Simulate the process day by day according to the plan.
 *   - Track the number of unknown-gender guinea pigs (u) and known-gender pairs (v).
 *   - When a doctor arrives (b_i == 2), all unknowns are resolved into pairs
 *     which can be merged into existing aviaries.
 *   - Use greedy strategy to determine minimum aviary count.
 *
 * Time Complexity: O(n) where n is the total number of days across all test cases.
 * Space Complexity: O(1) — only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long u(0), v(0), res(0); // u: unknown guinea pigs, v: known-pair count, res: max aviaries needed
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x == 1) {
        ++u; // Buy a new guinea pig (unknown gender)
      } else if (x == 2) {
        v += u; // Doctor arrives: all unknowns become known as pairs
        u = 0;
      }
      // Calculate current maximum needed aviaries:
      // u is unknown, v gives how many known pairs exist that can cohabit in one aviary
      long cur = u + (v > 0) * (v + 2) / 2;
      res = (res > cur) ? res : cur; // Keep track of maximum needed so far
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/