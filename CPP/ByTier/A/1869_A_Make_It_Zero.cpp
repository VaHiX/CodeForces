// Problem: CF 1869 A - Make It Zero
// https://codeforces.com/contest/1869/problem/A

/*
 * Problem: Make It Zero
 * Algorithm: Greedy approach based on array length parity
 * Time Complexity: O(n) per test case, where n is the length of the array
 * Space Complexity: O(1), only using a constant amount of extra space
 *
 * The strategy is:
 * - If the array length n is odd, we perform 4 operations:
 *   1. Operation on [2, n]: XOR the subarray from index 2 to n
 *   2. Operation on [2, n]: XOR the same subarray again
 *   3. Operation on [1, 2]: XOR the first two elements
 *   4. Operation on [1, 2]: XOR the first two elements again
 * - If the array length n is even, we perform 2 operations:
 *   1. Operation on [1, n]: XOR the entire array
 *   2. Operation on [1, n]: XOR the entire array again
 *
 * This ensures all elements become 0, as XOR of all elements with themselves
 * results in 0, and we are effectively "zeroing out" the array using these
 * operations.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
    }
    if (n % 2) {
      printf("4\n2 %ld\n2 %ld\n1 2\n1 2\n", n, n);
    } else {
      printf("2\n1 %ld\n1 %ld\n", n, n);
    }
  }
}


// https://github.com/VaHiX/CodeForces/