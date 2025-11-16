// Problem: CF 888 D - Almost Identity Permutations
// https://codeforces.com/contest/888/problem/D

/*
 * Problem: Count "almost identity" permutations
 * 
 * An almost identity permutation is one where at least (n - k) positions
 * have the property p[i] = i.
 * 
 * Approach:
 * - The total number of permutations is n!
 * - We calculate how many permutations have fewer than (n - k) fixed points
 *   using inclusion-exclusion principle or direct combinatorics.
 * - We break the problem into cases based on the number of fixed points,
 *   and sum up the valid permutations.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 * 
 * Algorithms/Techniques:
 * - Combinatorial mathematics
 * - Direct formulae for counting permutations with fixed points
 * 
 * The formula is derived as follows:
 * - Case 1: Exactly n fixed points (identity permutation) → 1 way
 * - Case 2: Exactly (n - 1) fixed points → C(n, 1) * D(n - 1) = n * D(n - 1)
 *   But since D(1) = 0, and D(2) = 1, etc., we simplify using direct calculation.
 * - Case 3: Exactly (n - 2) fixed points → C(n, 2) * D(n - 2)
 * - Case 4: Exactly (n - 3) fixed points → C(n, 3) * D(n - 3)
 * - Case 5: Exactly (n - 4) fixed points → C(n, 4) * D(n - 4)
 * 
 * We precompute coefficients based on derangements and combinations.
 * The final result sums contributions from all valid cases.
 */

#include <cstdio>
int main() {
  long long n, k;
  scanf("%lld %lld", &n, &k);
  // Precomputed values for derangements and combination multipliers
  long long res = 1 + (k >= 2) * (n * (n - 1) / 2) * 1 +
                  (k >= 3) * (n * (n - 1) * (n - 2) / 6) * 2 +
                  (k >= 4) * (n * (n - 1) * (n - 2) * (n - 3) / 24) * 9;
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/