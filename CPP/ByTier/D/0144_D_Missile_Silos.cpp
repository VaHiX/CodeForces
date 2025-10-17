/*
 * Problem URL : https://codeforces.com/problemset/problem/144/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
const int N = 202200;
int n, m, k, s, ans, u[N], v[N], w[N], f[N], dis[N];
vector<pii> e[N];
void dijkstra() {
  priority_queue<pii, vector<pii>, greater<pii>> q;
  for (int i = 1; i <= n; i++)
    dis[i] = 1e9 + 7;
  q.push({dis[s] = 0, s});
  while (q.size()) {
    int p = q.top().second;
    q.pop();
    if (f[p])
      continue;
    f[p] = 1;
    for (pii i : e[p])
      if (dis[i.first] > dis[p] + i.second)
        q.push({dis[i.first] = dis[p] + i.second, i.first});
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 1; i <= m; i++)
    scanf("%d%d%d", u + i, v + i, w + i), e[u[i]].push_back({v[i], w[i]}),
        e[v[i]].push_back({u[i], w[i]});
  scanf("%d", &k), dijkstra();
  for (int i = 1; i <= n; i++)
    ans += (dis[i] == k);
  for (int i = 1; i <= m; i++) {
    int x = u[i], y = v[i], z = w[i];
    if (2 * k == dis[x] + dis[y] + z)
      ans += (dis[x] < k && dis[y] < k);
    if (2 * k < dis[x] + dis[y] + z)
      ans += (dis[x] < k) + (dis[y] < k);
  }
  printf("%d", ans);
  return 0;
}