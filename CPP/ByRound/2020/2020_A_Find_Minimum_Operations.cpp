// Problem: CF 2020 A - Find Minimum Operations
// https://codeforces.com/contest/2020/problem/A

/*
 * Problem: Find Minimum Operations
 * Task: Given integers n and k, find the minimum number of operations to reduce n to 0,
 *       where each operation subtracts a power of k (k^x).
 *
 * Algorithm:
 * - This problem is equivalent to finding the sum of digits in base-k representation of n.
 * - Each digit in base-k represents how many times we subtract that power of k.
 * - For example, 5 in base-2 is 101, so we subtract 2^0=1 twice and 2^2=4 once,
 *   total operations = 1 + 0 + 1 = 2.
 *
 * Time Complexity: O(log_k(n)) per test case due to base-k digit sum calculation.
 * Space Complexity: O(1), only using constant extra space.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k == 1) {
      printf("%ld\n", n); // Special case: all operations must subtract 1
      continue;
    }
    long cnt(0);
    while (n) {
      cnt += n % k; // Count the number of operations for current digit
      n /= k;       // Move to next higher power
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/