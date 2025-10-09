/*
 * Problem URL : https://codeforces.com/contest/1029/problem/E
 * Submit Date : 2025-08-31
 */

#include <iostream>
#include <string.h>
#include <vector>
#define Fast                                                                   \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
using namespace std;
#define int long long
#define pb push_back
const int N = 200002;
vector<int> g[N];
int n, ans, dis[N];

void dfs(int u, int p) {
  for (auto to : g[u]) {
    if (to == p)
      continue;
    dis[to] = dis[u] + 1;
    dfs(to, u);
    if (dis[to] > 2) {
      ++ans;
      dis[u] = 1;
    }
    dis[u] = min(dis[to] + 1, dis[u]);
  }
}

signed main() {
  Fast;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(1, 0);
  cout << ans << endl;
  return 0;
}
