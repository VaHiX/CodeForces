// Problem: CF 1353 A - Most Unstable Array
// https://codeforces.com/contest/1353/problem/A

/*
 * Problem: A. Most Unstable Array
 * Purpose: Given n and m, construct an array of length n with non-negative integers
 *          such that the sum is exactly m and the sum of absolute differences
 *          between adjacent elements is maximized.
 *
 * Algorithm:
 * - If n <= 1: result is 0 (no adjacent pairs)
 * - If n == 2: result is m (put all value in one element, 0 in other)
 * - If n >= 3: result is 2 * m (alternate between 0 and max possible value)
 *
 * Time Complexity: O(t) where t is number of test cases
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    if (n <= 1) {
      puts("0");
    } else if (n <= 2) {
      printf("%ld\n", m);
    } else {
      printf("%ld\n", 2 * m);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/