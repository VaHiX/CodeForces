/*
 * Problem URL : https://codeforces.com/problemset/problem/2062/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 2;
int T, n, l[N], r[N], f[N];
long long tag;
vector<int> e[N];
void dfs(int u, int fa) {
  f[u] = l[u];
  for (int v : e[u])
    if (v != fa) {
      dfs(v, u);
      if (f[v] > f[u]) {
        if (f[v] > r[u])
          f[u] = r[u], tag += f[v] - r[u];
        else
          f[u] = f[v];
      }
    }
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n;
    tag = 0;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i <= n; ++i)
      cin >> l[i] >> r[i];
    for (int i = 1, u, v; i < n; ++i) {
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);
    }
    dfs(1, 0);
    cout << f[1] + tag << '\n';
  }
  return 0;
}
