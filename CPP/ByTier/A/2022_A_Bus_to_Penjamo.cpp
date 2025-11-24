// Problem: CF 2022 A - Bus to Pénjamo
// https://codeforces.com/contest/2022/problem/A

/*
 * Problem: A. Bus to Pénjamo
 * Algorithm: Greedy approach to maximize happy people by optimally placing families in bus rows.
 * Time Complexity: O(n) per test case, where n is the number of families.
 * Space Complexity: O(1), only using a few variables for computation.
 *
 * Each family member must be seated. A person is happy if:
 * - They are seated with another family member in the same row (both in same row),
 * - Or they are alone in their row with an empty seat next to them.
 *
 * Strategy:
 * - For each family, process how many people can sit together (as pairs) first.
 * - Use remaining seats (from pairs) to assign single people optimally.
 * - Count total happy people accordingly.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, r;
    scanf("%ld %ld", &n, &r);
    long cnt(0), rem(0); // cnt: total happy people count; rem: leftover single family members
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      // Add pairs (2 people per row) that are happy (each contributes 2 happy people)
      cnt += 2 * (a / 2);
      // Reduce number of available rows by half of the family size (as each pair fills 1 row)
      r -= a / 2;
      // Keep track of remaining single members
      rem += (a % 2);
    }
    // Handle remaining single members optimally:
    // If all can be paired with existing single people in rows, or some alone
    cnt += (rem <= r ? rem : (2 * r - rem));
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/