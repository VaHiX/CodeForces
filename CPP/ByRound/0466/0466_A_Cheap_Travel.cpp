// Problem: CF 466 A - Cheap Travel
// https://codeforces.com/contest/466/problem/A

/*
 * Problem: Cheap Travel
 * 
 * Purpose: Find the minimum cost for Ann to make 'n' subway rides,
 *          considering two options:
 *          1. Buy individual single-ride tickets (costs 'a' rubles each)
 *          2. Buy multi-ride tickets (costs 'b' rubles for 'm' rides)
 * 
 * Approach:
 * - Calculate how many complete multi-ride tickets we can buy (bundles = n / m)
 * - Calculate remaining single rides (singles = n % m)
 * - For bundles: choose cheaper between buying 'bundles' multi-ride tickets
 *   or buying individual single tickets for the same number of rides
 * - For remaining singles: choose cheaper between buying individual tickets
 *   or a new multi-ride ticket (if beneficial)
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only using a fixed number of variables
 */

#include <cstdio>
int main() {
  int n, m, a, b;
  scanf("%d %d %d %d", &n, &m, &a, &b);
  int bundles = n / m;        // Number of complete multi-ride tickets
  int singles = n % m;        // Remaining individual rides
  long total = 0;
  // Decide between buying multi-ride ticket or single tickets for bundles
  total += bundles * ((m * a < b) ? m * a : b);
  // Decide between buying single tickets or a new multi-ride ticket for remaining rides
  total += (singles * a < b) ? singles * a : b;
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/