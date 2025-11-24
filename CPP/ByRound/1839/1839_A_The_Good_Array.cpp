// Problem: CF 1839 A - The Good Array
// https://codeforces.com/contest/1839/problem/A

/*
 * Problem: A. The Good Array
 * Algorithm: Mathematical calculation to determine minimum number of ones in a good array.
 * Time Complexity: O(1) per test case
 * Space Complexity: O(1)
 *
 * For each position i, we need at least ceil(i/k) ones among the first i and last i elements.
 * The optimal strategy is to place ones in a way that minimizes total count.
 * This can be computed using ceiling division and adjustment logic.
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    // Calculate minimum number of ones needed:
    // - First term: ceil(n/k) = (n + k - 1) / k
    // - Second term: adds 1 if k > 1 and (n % k != 1), which handles edge cases correctly
    printf("%ld\n", ((n + k - 1) / k) + ((k > 1) && (n % k != 1)));
  }
}


// https://github.com/VaHiX/codeForces/