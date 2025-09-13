/*
 * Problem URL : https://codeforces.com/problemset/problem/2114/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
long long a[N], mn[N], mx[N];
vector<int> e[N];
void dfs(int u, int fa) {
  for (size_t i = 0; i < e[u].size(); i++) {
    int v = e[u][i];
    if (v == fa)
      continue;
    mx[v] = max(a[v], a[v] - mn[u]);
    mn[v] = min(a[v], a[v] - mx[u]);
    dfs(v, u);
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i], e[i].clear();
    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);
    }
    mx[1] = mn[1] = a[1];
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
      cout << mx[i] << " ";
    cout << "\n";
  }
  return 0;
}