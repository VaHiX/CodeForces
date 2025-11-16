// Problem: CF 1293 B - JOE is on TV!
// https://codeforces.com/contest/1293/problem/B

/*
 * Code Purpose: Calculates the maximum reward JOE can receive in the TV show "1 vs. n".
 *               The strategy is to maximize the sum of t/s for each round, where t is the number of
 *               opponents eliminated in that round and s is the number of opponents before elimination.
 *               The optimal strategy is to eliminate one opponent at a time, which leads to the
 *               harmonic series: 1/1 + 1/2 + 1/3 + ... + 1/n.
 *
 * Algorithms/Techniques: Harmonic Series Calculation
 *
 * Time Complexity: O(n) - loop runs n times
 * Space Complexity: O(1) - only using a constant amount of extra space
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long double res(0.0);  // Initialize result to 0
  for (long p = 1; p <= n; p++) {
    res += 1.0 / p;  // Add 1/p to the total reward (harmonic series)
  }
  printf("%.5Lf\n", res);  // Print result with sufficient precision
  return 0;
}


// https://github.com/VaHiX/CodeForces/