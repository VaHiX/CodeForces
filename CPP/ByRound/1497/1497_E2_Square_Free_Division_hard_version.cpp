// Problem: CF 1497 E2 - Square-Free Division (hard version)
// https://codeforces.com/contest/1497/problem/E2

/*
 * Problem: E2. Square-Free Division (hard version)
 *
 * Algorithm/Techniques:
 * - Preprocessing: Reduce each number to its square-free form by removing all
 * square factors.
 * - Sliding window: For each number of operations k, find the minimum number of
 * segments required.
 * - Dynamic Programming: Use DP to compute minimum segments with up to k
 * changes.
 *
 * Time Complexity: O(n * k * sqrt(max(a[i])) + n * k^2)
 * Space Complexity: O(n * k + max(a[i]))
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10, K = 25, S = 1e7 + 10;
const int inf = 0x3f3f3f3f;
int T, n, k;
int ans;
int a[N];
int num[S];
int f[N][K], g[N][K];

inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
    ch == '-' ? f = 0 : 0, ch = getchar();
  while (ch >= '0' && ch <= '9')
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return f ? x : -x;
}

inline int min(int a, int b) { return a < b ? a : b; }

int main() {
  T = read();
  while (T--) {
    n = read(), k = read(), ans = inf;
    for (int i = 1; i <= n; ++i) {
      a[i] = read();
      // Reduce each number to its square-free form
      for (int j = 2; j * j <= a[i]; ++j)
        while (a[i] % (j * j) == 0)
          a[i] /= j * j;
    }

    // Compute for all possible numbers of operations (0 to k)
    for (int i = 0; i <= k; ++i) {
      for (int j = 1; j <= n; ++j)
        num[a[j]] = 0;
      // Sliding window: for each window with at most i duplicates, find the
      // leftmost valid start
      for (int l = 1, r = 1, t = 0; r <= n; ++r) {
        ++num[a[r]], t += (num[a[r]] > 1);
        while (t > i && l < r)
          t -= (num[a[l]] > 1), --num[a[l]], ++l;
        g[r][i] = l;
      }
    }

    // Dynamic Programming: f[i][j] represents the minimum segments needed for
    // first i elements with j operations
    for (int i = 1; i <= n; ++i)
      for (int j = 0; j <= k; ++j) {
        f[i][j] = inf;
        for (int x = 0; x <= j; ++x)
          f[i][j] = min(f[i][j], f[g[i][x] - 1][j - x] + 1);
      }

    // Find minimum answer among all possible operations from 0 to k
    for (int i = 0; i <= k; ++i)
      ans = min(ans, f[n][i]);

    printf("%d\n", ans);
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/