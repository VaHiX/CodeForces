// Problem: CF 2009 F - Firefly's Queries
// https://codeforces.com/contest/2009/problem/F

/*
F. Firefly's Queries
time limit per test2 seconds
memory limit per test256 megabytes

Problem Description:
Given an array a of length n, we generate a new array b by concatenating all cyclic shifts of a.
Each cyclic shift c_i is defined as shifting elements such that the i-th element becomes the first.
Then, for each query (l, r), compute the sum of elements from index l to r in b.

Approach:
- Preprocess prefix sums of twice the array to handle cyclic shifts efficiently.
- For each query, calculate prefix sums using modular arithmetic and offset handling.
- Time Complexity: O(n + q) per test case
- Space Complexity: O(n)

Algorithms/Techniques:
- Prefix Sum Array
- Modular Arithmetic for Cyclic Shift Handling
- Range Queries with Preprocessing
*/

#include <stdio.h>

long long a[400005]; // Sufficient size to hold 2*n elements (including wraparound)
int T, n, m;

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", &a[i]), a[n + i] = a[i]; // Duplicate array to handle wraparound
    for (int i = 1; i <= (n << 1); ++i)
      a[i] += a[i - 1]; // Build prefix sum array of length 2*n

    for (long long l, r; m--;) {
      scanf("%lld%lld", &l, &r);
      // Compute the total sum from l to r in b using precomputed prefix sums
      printf("%lld\n", (r / n - (l - 1) / n - 1) * a[n] +
                           a[(l - 1) / n % n + n] -
                           a[(l - 1) / n % n + (l - 1) % n] +
                           a[r / n % n + r % n] - a[r / n % n]);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/