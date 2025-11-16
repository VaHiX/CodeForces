// Problem: CF 2049 D - Shift + Esc
// https://codeforces.com/contest/2049/problem/D

/*
D. Shift + Esc
Algorithms/Techniques: Dynamic Programming with State Compression, Grid Path Finding with Cyclic Shift Operations

Time Complexity: O(n * m^2)
Space Complexity: O(n * m)

Problem:
Given a grid of n rows and m columns, find the minimum cost path from (1,1) to (n,m) where:
- You can only move right or down.
- Before moving, you may cyclically shift any row left by some amount.
- Cost = k * x + y, where x = number of shifts, y = sum of path values.

Approach:
- Use dynamic programming: dp[i][j] stores the minimum cost to reach cell (i,j).
- f[k][j] represents the cost for shifting row i by k positions and reaching column j.
- For each row, precompute all possible shifts and store the minimal cost to reach that column.

*/

#include <algorithm>
#include <cstdio>

using namespace std;
constexpr int N = 2e2 + 5;
constexpr long long MAX_LONG = 1e18;
long long dp[N][N], f[N][N];
int a[N];

void work() {
  int n, m, K;
  scanf("%d%d%d", &n, &m, &K);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++)
      scanf("%d", &a[j]);
    for (int j = 0; j < m; j++) {
      long long mi = 1e18;
      for (int k = 0; k < m; k++) {
        // f[k][j] calculates the minimal cost at column j if we shift row i by k positions
        // We consider two cases:
        // 1. From previous column in same row -> f[k][j-1]
        // 2. From last row at column j -> dp[i-1][j] + cost to shift (if applicable)
        f[k][j] = min(j ? f[k][j - 1] : MAX_LONG,
                      (i > 1 || !j) ? dp[i - 1][j] + 1ll * k * K : MAX_LONG) +
                  a[(j + k) % m];
        mi = min(f[k][j], mi); // Track the minimum for current column j
      }
      dp[i][j] = mi;  // Minimum cost to reach row i, column j
    }
  }
  printf("%lld\n", dp[n][m - 1]);  // Output the result for the last cell
}

int main() {
  int t = 1;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/