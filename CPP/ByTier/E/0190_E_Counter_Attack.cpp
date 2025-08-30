/*
 * Problem URL : https://codeforces.com/problemset/problem/190/E
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
vector<int> ed[500005];
int pa[500005];
int find(int i) {
  if (!pa[i])
    return i;
  return pa[i] = find(pa[i]);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    ed[u].pb(v);
    ed[v].pb(u);
  }
  for (int i = 1; i <= n; i++) {
    sort(ed[i].begin(), ed[i].end());
  }
  vector<int> res[n];
  int e = 0;
  for (int u = 1; u <= n; u = find(u + 1)) {
    pa[u] = find(u + 1);
    vector<int> q;
    int ss = 0;
    q.pb(u);
    res[e].pb(u);
    while (ss < q.size()) {
      int u = q[ss];
      int k = 0;
      for (int i = find(2); i <= n; i = find(i + 1)) {
        for (; k < ed[u].size() && i > ed[u][k]; k++)
          ;
        if (k == ed[u].size() || ed[u][k] != i) {
          q.pb(i);
          res[e].pb(i);
          pa[i] = find(i + 1);
        }
      }
      ss++;
    }
    e++;
  }
  cout << e << "\n";
  for (int i = 0; i < e; i++) {
    cout << res[i].size() << " ";
    for (int j : res[i])
      cout << j << " ";
    cout << "\n";
  }
}
// hellobig_tq//hellobig_tq