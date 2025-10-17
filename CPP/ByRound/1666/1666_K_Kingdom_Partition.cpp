/*
 * Problem URL : https://codeforces.com/contest/1666/problem/K
 * Submit Date : 2025-09-08
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e15;
const int maxn = 1005;
const int maxe = maxn * 4 + 2005 * 4;
int n, m, i, j, t, k, s, head[maxn << 1], N, S, T, pa, pb;
ll ans;
struct Edge {
  int nxt, aim;
  ll len;
} edge[maxe];
inline void add_edge(int x, int y, ll z) {
  edge[++N] = (Edge){head[x], y, z};
  head[x] = N;
  edge[++N] = (Edge){head[y], x, z};
  head[y] = N;
}
queue<int> Q;
int dis[maxn << 1], cur[maxn << 1];
inline bool bfs() {
  memset(dis, 0x3f3f3f3f, sizeof(dis));
  dis[S] = 0;
  Q.push(S);
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    cur[x] = head[x];
    for (int i = head[x]; ~i; i = edge[i].nxt)
      if (edge[i].len > 0) {
        int des = edge[i].aim;
        if (dis[des] > dis[x] + 1) {
          dis[des] = dis[x] + 1;
          Q.push(des);
        }
      }
  }
  return dis[T] < 1e9;
}
ll dfs(int x, ll y) {
  if (x == T)
    return y;
  ll used = 0;
  for (int i = cur[x]; ~i; i = edge[i].nxt) {
    int des = edge[i].aim;
    cur[x] = i;
    if (dis[des] != dis[x] + 1 || edge[i].len == 0)
      continue;
    ll ff = dfs(des, min(y - used, edge[i].len));
    edge[i].len -= ff;
    edge[i ^ 1].len += ff;
    used += ff;
    if (y == used)
      return y;
  }
  return used;
}

int main() {
  memset(head, 0xff, sizeof(head));
  N = -1;
  scanf("%d%d", &n, &m);
  scanf("%d%d", &pa, &pb);
  S = n * 2 + 1;
  T = S + 1;
  add_edge(S, pa, INF);
  add_edge(pa + n, T, INF);
  add_edge(pb, T, INF);
  add_edge(S, pb + n, INF);
  for (i = 1; i <= m; ++i)
    scanf("%d%d%d", &t, &k, &s), add_edge(t, k + n, s), add_edge(k, t + n, s);
  while (bfs())
    ans += dfs(S, INF);
  printf("%lld\n", ans);
  for (i = 1; i <= n; ++i) {
    bool f0 = (dis[i] < 1e9), f1 = (dis[i + n] < 1e9);
    if (f0 == f1)
      putchar('C');
    else if (f0)
      putchar('A');
    else
      putchar('B');
  }
  puts("");
  return 0;
}
