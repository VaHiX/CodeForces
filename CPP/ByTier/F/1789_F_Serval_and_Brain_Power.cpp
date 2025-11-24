// Problem: CF 1789 F - Serval and Brain Power
// https://codeforces.com/contest/1789/problem/F

/*
Code Purpose:
This code finds the length of the longest "powerful" subsequence in a given string.
A powerful subsequence is one that can be represented as a repetition of a base string (k times where k >= 2).
The algorithm uses dynamic programming for finding longest common subsequences (LCS) up to 3 sequences,
and brute-force DFS to try possible patterns for repeatable substrings.

Algorithms/Techniques:
- Dynamic Programming (LCS for 2 and 3 sequences)
- Depth-First Search (DFS) for brute-forcing potential repeating patterns
- Subsequence matching with repetition check

Time Complexity:
O(N^3) where N is the length of the input string due to nested loops and LCS computations.
In practice, given N <= 80, this is acceptable.
Space Complexity:
O(N^2) for 2D DP arrays (f) and O(N^3) for 3D DP arrays (g), making total space complexity O(N^3).
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define ll long long
#define N 83
#define mkp make_pair
#define pb push_back
#define dbl double
using namespace std;
ll read() {
  ll x = 0, fl = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      fl = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * fl;
}
int n;
char a[N];
int f[N][N], g[N][N][N], s[N], cnt;
int ans;
int lcs2(int l1, int r1, int l2, int r2) {
  // Reset DP table for lcs2
  for (int i = l1 - 1; i <= r1 + 1; i++) {
    for (int j = l2 - 1; j <= r2 + 1; j++)
      f[i][j] = 0;
  }
  // Compute LCS for two sequences from l1 to r1 and l2 to r2
  for (int i = l1; i <= r1; i++) {
    for (int j = l2; j <= r2; j++) {
      f[i][j] =
          max(max(f[i - 1][j], f[i][j - 1]), f[i - 1][j - 1] + (a[i] == a[j]));
    }
  }
  return f[r1][r2];
}
int lcs3(int l1, int r1, int l2, int r2, int l3, int r3) {
  // Reset DP table for lcs3
  for (int i = l1 - 1; i <= r1 + 1; i++) {
    for (int j = l2 - 1; j <= r2 + 1; j++) {
      for (int k = l3 - 1; k <= r3 + 1; k++)
        g[i][j][k] = 0;
    }
  }
  // Compute LCS for three sequences from l1 to r1, l2 to r2, l3 to r3
  for (int i = l1; i <= r1; i++) {
    for (int j = l2; j <= r2; j++) {
      for (int k = l3; k <= r3; k++) {
        g[i][j][k] =
            max(max(g[i - 1][j][k], max(g[i][j - 1][k], g[i][j][k - 1])),
                g[i - 1][j - 1][k - 1] + (a[i] == a[j] && a[j] == a[k]));
      }
    }
  }
  return g[r1][r2][r3];
}
int check() {
  // Check if s forms a powerful string from a
  int sz = 0;
  for (int i = 1, j = 1; i <= n; i++) {
    if (a[i] == s[j]) {
      j++;
      if (j == cnt + 1)
        j = 1, sz++; // Loop back to start of pattern
    }
  }
  return sz > 1 ? sz * cnt : 0; // If pattern repeated more than once, return length
}
void dfs(int x, int jl) {
  // DFS to try building a repeating pattern
  if (jl == 16 || x == n + 1) {
    ans = max(ans, check());
    return;
  }
  dfs(x + 1, jl + 1); // Skip current character
  s[++cnt] = a[x], dfs(x + 1, jl + 1), cnt--; // Include current character
}
int main() {
  scanf("%s", a + 1);
  n = strlen(a + 1);
  // Try all combinations of two substrings to form a powerful subsequence
  for (int i = 1; i < n; i++) {
    ans = max(ans, 2 * lcs2(1, i, i + 1, n));
  }
  // Try all combinations of three substrings
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ans = max(ans, 3 * lcs3(1, i, i + 1, j, j + 1, n));
    }
  }
  // Start DFS from every 16th character to avoid too many possibilities
  for (int i = 1; i <= n; i += 16) {
    dfs(i, 0);
  }
  printf("%d", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/