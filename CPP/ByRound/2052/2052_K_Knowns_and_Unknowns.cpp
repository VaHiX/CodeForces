/*
 * Problem URL : https://codeforces.com/problemset/problem/2052/K
 * Submit Date : 2025-08-24
 */

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;
constexpr int N = 2e3;
int p[2][N], q[2][N], ng[2], bnd[2][N], gs[2][N], gn[2][N], vis[N], used[N];
vector<int> gm[2][N], mt[N];
bitset<2 * N> a[2 * N];
bool try_match(int v) {
  if (!vis[v]++)
    for (auto x : gm[0][v])
      if (!used[x]) {
        int u = gn[1][x];
        if (mt[u].size() < gs[1][u])
          return mt[u].push_back(x), used[x] = 1;
        for (auto &xx : mt[u])
          if (try_match(gn[0][xx]))
            return used[xx] = 0, xx = x, used[x] = 1;
      }
  return 0;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; mt[i].clear(), ++i)
      for (int c : {0, 1})
        gm[c][i].clear();
    for (int i = 0; i < 2 * n; ++i)
      a[i].reset();
    ng[0] = ng[1] = 0;
    for (int c : {0, 1})
      for (int i = 0; i < n; ++i)
        cin >> p[c][i], q[c][--p[c][i]] = i;
    int k;
    cin >> k;
    int t = 2 * k;
    for (int c : {0, 1}) {
      int j = 0;
      for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        --t;
        if (~x) {
          --x;
          if (bnd[c][ng[c]] + i - j > q[c][x])
            goto fail;
          if (bnd[c][ng[c]] != q[c][x])
            gs[c][ng[c]] = i - j, bnd[c][++ng[c]] = q[c][x];
          gs[c][ng[c]] = 1;
          bnd[c][++ng[c]] = q[c][x] + 1;
          j = i + 1;
        }
      }
      if (bnd[c][ng[c]] < n)
        gs[c][ng[c]] = k - j, bnd[c][++ng[c]] = n;
      for (int i = 0, j = 0; i < n; ++i, j += i == bnd[c][j + 1])
        gm[c][j].push_back(p[c][i]), gn[c][p[c][i]] = j;
    }
    fill(used, used + n, 0);
    int sz;
    for (int i = sz = 0; i < n; ++i)
      if (gs[0][gn[0][i]]-- > 0) {
        sz += try_match(gn[0][i]);
        fill(vis, vis + n, 0);
      }
    if (sz < k) {
    fail:;
      while (t--)
        cin >> sz;
      cout << "Inconsistent\n";
      continue;
    }
    for (int x = 0; x < n; ++x)
      a[used[x] * n + gn[used[x]][x]][!used[x] * n + gn[!used[x]][x]] = 1;
    for (int i = 0; i < 2 * n; ++i)
      for (int j = 0; j < 2 * n; ++j)
        if (a[j][i])
          a[j] |= a[i];
    for (int x = 0; x < n; ++x)
      cout << "Y?N"[a[gn[0][x]][n + gn[1][x]] + 1 - a[n + gn[1][x]][gn[0][x]]];
    cout << '\n';
  }
}
