// Problem: CF 2113 C - Smilo and Minecraft
// https://codeforces.com/contest/2113/problem/C

/*
C. Smilo and Minecraft

Purpose:
This code solves the problem where Smilo can place dynamite on empty cells in a grid mine.
When a dynamite explodes at position (x, y), it creates an explosion square of side 2k+1 centered at that point.
Gold ores located strictly inside this square disappear but those on the boundary are collected.
The goal is to determine the maximum number of golds Smilo can collect.

Algorithms/Techniques:
- 2D Prefix Sum: Used to efficiently compute the number of gold cells in any rectangular subregion.
- Brute Force + Prefix Sum Optimization: For each empty cell, simulate placing dynamite and calculate how much gold can be collected.

Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for storing prefix sums and grid data.

*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int N = 500 + 1;
int n, m, k;
char s[N][N];
int cnt[N][N]; // Prefix sum array to count golds in submatrices

// Function to get the number of 'g' in a square around (x,y) with radius k
int getg(int x, int y) {
  int l = max(y - k, 1), u = max(x - k, 1);             // Left and top boundaries
  int r = min(y + k, m), d = min(x + k, n);             // Right and bottom boundaries
  return cnt[d][r] - cnt[d][l - 1] - cnt[u - 1][r] + cnt[u - 1][l - 1]; // Compute sum using prefix sums
}

void work() {
  scanf("%d%d%d", &n, &m, &k);
  k--; // Adjust k to make it zero-based indexing for square radius

  for (int i = 1; i <= n; i++)
    scanf("%s", s[i] + 1); // Read grid, 1-indexed

  // Build prefix sum array
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cnt[i][j] =
          cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] + (s[i][j] == 'g');

  int tot = cnt[n][m], ans = 0; // Total gold count, max gold we can collect

  // Try detonating dynamite at every empty cell ('.') to see how much gold is collected
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (s[i][j] == '.') // Only test on empty cells
        ans = max(ans, tot - getg(i, j)); // Maximize total gold minus gold destroyed by explosion

  printf("%d\n", ans);
  return;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}


// https://github.com/VaHiX/codeForces/