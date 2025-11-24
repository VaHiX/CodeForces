// Problem: CF 2108 A - Permutation Warm-Up
// https://codeforces.com/contest/2108/problem/A

/*
 * Problem: Count distinct values of function f(p) = sum of |p[i] - i| over all permutations of 1..n
 * Algorithm: Mathematical observation and pattern recognition
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * For a permutation of length n, the function f(p) can take values from 0 up to a maximum.
 * The minimum value is always 0 (when p[i] = i for all i).
 * The maximum value occurs when elements are as far apart as possible.
 * Through analysis, the formula for number of distinct values is:
 *   1 + n*n / 4
 *
 * This works because:
 * - The range of f(p) is from 0 to (n*(n-1)/2)
 * - But due to symmetry and combinatorial properties of permutations,
 *   only certain discrete values are achievable.
 * - A closed-form formula gives us the count directly.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%lld\n", 1 + (long long)n * n / 4); // Compute and print the number of distinct values
  }
}


// https://github.com/VaHiX/codeForces/