/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/D2
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N = 105, M = 10005, P = 1e9 + 7;
int n, c, m, a[M], C[N][N], f[N][M], ct[N][M], R[N];
void Inc(int &x, int y) {
  if ((x += y) >= P)
    x -= P;
}
void solve() {
  scanf("%d%d%d", &n, &c, &m), C[0][0] = 1;
  rep(i, 1, c) {
    C[i][0] = 1;
    rep(j, 1, c) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
  }
  rep(i, 1, m) scanf("%d", &a[i]);
  rep(i, 1, n) R[i] = 0;
  rep(i, 1, m) R[a[i]] = max(R[a[i]], i);
  rep(i, 0, n + 1) rep(j, 0, m + 1) ct[i][j] = 0;
  rep(i, 1, m) ct[a[i]][i]++;
  rep(i, 1, n) rep(j, 1, m) ct[i][j] += ct[i][j - 1];
  rep(j, 1, m) per(i, n - 1, 1) ct[i][j] += ct[i + 1][j];
  rep(i, 0, n) rep(j, 0, m) f[i][j] = 0;
  f[0][0] = 1;
  rep(i, 1, n) rep(j, 0, m - c) if (f[i - 1][j]) {
    int r = j + c;
    if (R[i] > r)
      continue;
    int x = ct[i][r] - ct[i + 1][r], y = r - ct[i + 1][r] - j;
    rep(k, x, y) Inc(f[i][j + k], 1ll * f[i - 1][j] * C[y - x][k - x] % P);
  }
  printf("%d\n", f[n][m]);
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--)
    solve();
}