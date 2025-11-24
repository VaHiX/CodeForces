// Problem: CF 1770 B - Koxia and Permutation
// https://codeforces.com/contest/1770/problem/B

/*
 * Problem: Koxia and Permutation
 * Algorithm: Greedy approach to construct a permutation that minimizes the maximum
 *            value of the sum of max and min in all sliding windows of size k.
 *
 * Approach:
 * - We alternate between picking from the highest remaining number and the lowest,
 *   starting with the highest for odd positions.
 * - This helps distribute large numbers across different windows, minimizing the
 *   maximum sum of max and min in any window.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1) (ignoring input/output)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long left(1), right(n);  // two pointers to manage numbers from 1 to n
    for (long p = 1; p <= n; p++) {
      if (p % 2) {  // if odd position, take from right (larger numbers)
        printf("%ld ", right);
        --right;
      } else {  // if even position, take from left (smaller numbers)
        printf("%ld ", left);
        ++left;
      }
    }
    puts("");  // newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/