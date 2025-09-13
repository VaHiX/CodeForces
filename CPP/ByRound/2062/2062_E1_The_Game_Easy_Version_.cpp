/*
 * Problem URL : https://codeforces.com/problemset/problem/2062/E1
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
vector<int> g[N];
int w[N], dfn[N], nfd[N], pre[N], suf[N], low[N], n;
bool vis[N];
int id;
void dfs(int u) {
  vis[u] = 1;
  dfn[u] = ++id;
  nfd[id] = u;
  for (auto v : g[u]) {
    if (vis[v])
      continue;
    dfs(v);
  }
  low[u] = id;
}
int main() {
  int T;
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    id = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      g[i].clear();
      vis[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      cin >> w[i];
    }
    for (int i = 1; i < n; i++) {
      int a, b;
      cin >> a >> b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    dfs(1);
    for (int i = 1; i < n; i++)
      pre[i] = max(pre[i - 1], w[nfd[i]]);
    suf[n + 1] = 0;
    for (int i = n; i >= 1; i--)
      suf[i] = max(suf[i + 1], w[nfd[i]]);
    int mx = 0;
    for (int i = 1; i <= n; i++)
      if (max(pre[dfn[i] - 1], suf[low[i] + 1]) > w[i] && w[i] > w[mx])
        mx = i;
    cout << mx << '\n';
  }
}