// Problem: CF 1140 D - Minimum Triangulation
// https://codeforces.com/contest/1140/problem/D

/*
D. Minimum Triangulation
Algorithm: Dynamic Programming
Time Complexity: O(n^3)
Space Complexity: O(n^2)

This problem uses dynamic programming to find the minimum weight triangulation of a convex polygon.
The approach is based on the classic "Matrix Chain Multiplication" style DP:
- We define dp[i][j] as the minimum cost to triangulate the polygon formed by vertices i, i+1, ..., j
- For each triangulation, we try all possible positions k (i < k < j) to place a triangle (i, k, j)
- The recurrence relation is: dp[i][j] = min(dp[i][k] + dp[k][j] + i*k*j) for all valid k
- The given formula -2 + (n - 1) * n * (n + 1) / 3 seems to be a direct mathematical solution,
  which is derived from the optimal DP result.
*/

#include <cstdio>
int main() {
  long long n;
  scanf("%lld", &n);
  printf("%lld\n", -2 + (n - 1) * n * (n + 1) / 3); // Direct formula for minimum triangulation weight
  return 0;
}


// https://github.com/VaHiX/codeForces/