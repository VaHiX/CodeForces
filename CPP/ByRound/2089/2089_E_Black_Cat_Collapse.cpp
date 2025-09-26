/*
 * Problem URL : https://codeforces.com/problemset/problem/2089/E
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int maxn = 90, mo = 998244353;

int T;

int n, sz[maxn], tmp[maxn], C[maxn][maxn], h[maxn][maxn], g[maxn][maxn],
    f[maxn][maxn][maxn];
vector<int> e[maxn];

inline int add(int x, int y) {
  x += y;
  return x < mo ? x : x - mo;
}

inline void upd(int &x, int y) {
  x = add(x, y);
  return;
}

void clean() {
  for (int i = 1; i <= n; ++i)
    vector<int>().swap(e[i]);
  memset(sz, 0, sizeof(sz));
  memset(h, 0, sizeof(h));
  memset(g, 0, sizeof(g));
  memset(f, 0, sizeof(f));
}

void solve() {
  clean();

  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    if (u > v)
      swap(u, v);
    e[u].emplace_back(v);
  }

  C[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = C[i][0] = 1; j <= i; ++j)
      C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
  }

  f[n + 1][0][0] = 1;
  for (int i = n; i; --i) {
    h[i][0] = 1;
    for (int x : e[i]) {
      fill(tmp, tmp + sz[i] + sz[x] + 1, 0);
      for (int j = 0; j <= sz[i]; ++j) {
        for (int k = 0; k <= sz[x]; ++k)
          upd(tmp[j + k], (i64)h[i][j] * h[x][k] % mo * C[j + k][j] % mo);
      }
      sz[i] += sz[x];
      for (int j = 0; j <= sz[i]; ++j)
        h[i][j] = tmp[j];
    }

    for (int j = 0; j <= sz[i]; ++j)
      g[i][j + 1] = h[i][j];
    sz[i]++;
    for (int j = sz[i]; j; --j)
      upd(h[i][j], h[i][j - 1]);

    for (int j = 0; j <= n - i; ++j) {
      for (int k = j; k <= n; ++k) {
        if (!f[i + 1][j][k])
          continue;
        if (i > 1)
          upd(f[i][j][k], f[i + 1][j][k]);
        for (int l = k + 1; l <= n - i + 1; ++l)
          upd(f[i][j + 1][l], f[i + 1][j][k]);
      }
    }

    int v = i + sz[i];
    for (int j = 0; j <= n - v + 1; ++j) {
      for (int k = j; k <= n; ++k) {
        if (!f[v][j][k])
          continue;
        for (int l = 1; l <= min(k - j, sz[i]); ++l)
          upd(f[i][j + l][k],
              (i64)f[v][j][k] * C[k - j][l] % mo * g[i][l] % mo);
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    cout << f[1][i][i] << " \n"[i == n];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> T;
  while (T--)
    solve();

  return 0;
}