// Problem: CF 1716 E - Swap and Maximum Block
// https://codeforces.com/contest/1716/problem/E

/*
 * Problem: E. Swap and Maximum Block
 * 
 * Purpose:
 *   This code efficiently processes queries on an array where each query
 *   swaps elements at positions i and i + 2^k, and then computes the maximum
 *   subarray sum of the modified array. Uses a segment tree-like approach with
 *   dynamic programming to maintain prefix and suffix sums and maximum subarray
 *   sums during swaps.
 *
 * Algorithms/Techniques:
 *   - Segment Tree with Dynamic Programming
 *   - Bit manipulation for tracking swaps
 *   - Preprocessing all possible swaps using bit operations
 *
 * Time Complexity:
 *   - Preprocessing: O(n * 2^n)
 *   - Each query: O(1)
 *   - Total: O(n * 2^n + q)
 *
 * Space Complexity:
 *   - O(n * 2^n) for DP table
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define N 300000
#define b long long
int n, a[N], x, m, q;
struct rua {
  b r, s, sl, sr;
} f[20][N];
int main() {
  scanf("%d", &n);
  // Initialize base case (level 0) of the DP table with single elements
  for (int i = 0; i < (1 << n); i++)
    scanf("%d", &x), f[0][i] = {max(0, x), x, x, x}, a[i] = x;
  // Build up DP table for all levels from 1 to n
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < (1 << n); j++) {
      int k = j ^ (1 << i - 1); // XOR to find the corresponding element
      // Compute max subarray sum, total sum, left and right prefix/suffix sums
      f[i][j].r =
          max({f[i - 1][j].r, f[i - 1][k].r, f[i - 1][j].sr + f[i - 1][k].sl});
      f[i][j].s = f[i - 1][j].s + f[i - 1][k].s;
      f[i][j].sl = max(f[i - 1][j].sl, f[i - 1][j].s + f[i - 1][k].sl);
      f[i][j].sr = max(f[i - 1][k].sr, f[i - 1][k].s + f[i - 1][j].sr);
    }
  scanf("%d", &q);
  // Process queries
  while (q--)
    scanf("%d", &x), m ^= 1 << x, printf("%lld\n", f[n][m].r);
}


// https://github.com/VaHiX/CodeForces/