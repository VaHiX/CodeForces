// Problem: CF 1566 A - Median Maximization
// https://codeforces.com/contest/1566/problem/A

/*
 * Problem: Median Maximization
 * Algorithm: Greedy approach to maximize the median of an array with given sum.
 * Time Complexity: O(t), where t is the number of test cases.
 * Space Complexity: O(1).
 *
 * For each test case:
 * - We want to maximize the median of an array of n non-negative integers that sum to s.
 * - The optimal strategy is to place as much value as possible at the median position,
 *   while keeping the rest minimal (i.e., 0) to save sum for higher positions.
 *
 * Key insight:
 * - To maximize the median at position ceil(n/2), we must ensure that elements before it
 *   are minimized (set to 0).
 * - The median position is (n + 1) / 2 in 1-based indexing.
 * - If we place value 'x' at the median, we can distribute s - x among other positions.
 * - To keep the sum fixed and maximize x:
 *   - First n/2 elements are set to 0 (to minimize their contribution to the median).
 *   - The rest of the positions have to account for remaining sum.
 * - We compute how large the median can be by distributing sum optimally:
 *   - Remaining sum after placing minimum possible values in first half = s - (n/2)*0 = s
 *   - But we also need to allocate sum for the positions after median.
 *   - The correct formula simplifies to: s / (n - (n-1)/2)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s;
    scanf("%ld %ld", &n, &s);
    printf("%ld\n", s / (n - (n - 1) / 2)); // Compute maximum possible median using derived formula
  }
}


// https://github.com/VaHiX/codeForces/