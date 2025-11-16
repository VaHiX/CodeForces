// Problem: CF 1776 B - Vittorio Plays with LEGO Bricks
// https://codeforces.com/contest/1776/problem/B

/*
Code Purpose:
This code solves the problem of finding the minimum number of additional LEGO bricks needed to support a structure of purple bricks placed at specific x-coordinates and height h.
It uses dynamic programming with interval decomposition to compute the minimal supporting bricks required.

Algorithms/Techniques:
- Dynamic Programming (DP)
- Interval DP with memoization
- Segment-based computation for brick coverage

Time Complexity:
O(n^3) where n is the number of purple bricks. The nested loops over intervals and split points contribute to cubic complexity.

Space Complexity:
O(n^2) for the DP table and auxiliary arrays used for storing intermediate results.

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 305;
int n, h, T, k, a[N], H[N][N];
long long dp[N][N];
struct E {
  int l, to;
} e[N << 1];
;
void slv() {
  scanf("%d %d", &n, &h);
  memset(dp, 63, sizeof(dp)); // Initialize dp with a large value (infinity)
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]); // Read x-coordinates of purple bricks
  for (int i = n; i; --i) { // Process intervals from right to left
    for (int j = i; j <= n; ++j) {
      H[i][j] = (a[j] - a[i] + 1) / 2; // Compute the half-width of the interval [i, j]
      if (i == j)
        dp[i][j] = 0; // Base case: single brick requires no support
      if (H[i][j] > h)
        break; // If interval exceeds height h, skip further processing
      for (int k = i; k < j; ++k) {
        // Compute cost of splitting the interval into [i,k] and [k+1,j]
        int w = H[i][j] * 2 - 1 - H[i][k] - H[k + 1][j];
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + w); // Update minimal cost
      }
    }
  }
  for (int i = n; i; --i) { // Second pass to adjust for height differences
    for (int j = i; j <= n; ++j) {
      if (H[i][j] < h)
        dp[i][j] += h - H[i][j]; // Add the difference in height
      for (int k = i; k < j; ++k) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]); // Update based on subproblems
      }
    }
  }
  printf("%lld\n", dp[1][n]); // Output minimum bricks needed for entire structure
}
int main() {
  T = 1;
  while (T--)
    slv();
  return 0;
}


// https://github.com/VaHiX/CodeForces/