/*
 * Problem URL : https://codeforces.com/contest/1725/problem/M
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define INF 1e18
const int N = 2e6 + 10;
int n, m, beg[N], nex[N], to[N], w[N], e;
inline void add(int x, int y, int z) {
  ++e;
  nex[e] = beg[x];
  beg[x] = e;
  to[e] = y;
  w[e] = z;
}
ll dis[N];
int vis[N];
priority_queue<pair<ll, int>> Q;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    add(i, i + n, 0);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w), add(v + n, u + n, w);
  }
  Q.push(make_pair(0, 1));
  for (int i = 2; i <= n + n; i++)
    dis[i] = INF;
  while (!Q.empty()) {
    int x = Q.top().second;
    Q.pop();
    if (vis[x])
      continue;
    vis[x] = 1;
    for (int i = beg[x]; i; i = nex[i]) {
      int t = to[i];
      if (dis[t] > dis[x] + w[i])
        dis[t] = dis[x] + w[i], Q.push(make_pair(-dis[t], t));
    }
  }
  for (int i = n + 2; i <= n + n; i++)
    printf("%lld ", dis[i] == INF ? -1 : dis[i]);
  return 0;
}