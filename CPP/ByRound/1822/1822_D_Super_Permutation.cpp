// Problem: CF 1822 D - Super-Permutation
// https://codeforces.com/contest/1822/problem/D

/*
 * Code Purpose:
 * This code solves the "Super-Permutation" problem. Given an integer n,
 * it attempts to construct a permutation of length n such that when we compute
 * prefix sums modulo n and then add 1 to each result, we get another permutation.
 *
 * Algorithm:
 * - For n = 1, the only permutation [1] is a super-permutation.
 * - For odd n, it's impossible to construct a super-permutation, hence output -1.
 * - For even n > 1, a specific construction is used:
 *   - Even indices (0, 2, 4, ...) are filled with values n, n-2, n-4, ...
 *   - Odd indices (1, 3, 5, ...) are filled with values 1, 3, 5, ...
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) excluding input/output
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n == 1) {
      puts("1");
      continue;
    }
    if (n % 2) {
      puts("-1");
      continue;
    }
    for (long p = 0; p < n; p++) {
      // If p is odd, use p (1, 3, 5, ...)
      // If p is even, use (n - p) (n, n-2, n-4, ...)
      printf("%ld ", p % 2 ? p : (n - p));
    }
    puts("");
  }
}


// https://github.com/VaHiX/CodeForces/