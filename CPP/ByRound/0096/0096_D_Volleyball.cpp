/*
 * Problem URL : https://codeforces.com/problemset/problem/96/D
 * Submit Date : 2025-08-16
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <vector>
using namespace std;
#define fuck(x) cerr << #x << ' ' << x << endl
#define lson t << 1
#define rson t << 1 | 1
typedef long long ll;
int n, m, x, y;
struct node {
  int to, nex;
  ll val;
} edge[2005];
ll dp[1005];
int head[1005], cnt, vis[1005], za[1005];
ll dis[1005];
queue<int> sp;
void solve(int t) {
  while (!sp.empty())
    sp.pop();
  memset(za, 0, sizeof(za));
  for (int i = 0; i <= n; i++) {
    dis[i] = 100000000000000000ll;
  }
  dis[t] = 0;
  za[t] = 1;
  sp.push(t);
  while (!sp.empty()) {
    int f = sp.front();
    za[f] = 0;
    sp.pop();
    for (int i = head[f]; ~i; i = edge[i].nex) {
      int v = edge[i].to;
      if (dis[f] + edge[i].val < dis[v]) {
        dis[v] = dis[f] + edge[i].val;
        if (!za[v]) {
          za[v] = 1;
          sp.push(v);
        }
      }
    }
  }
}
pair<ll, ll> e[1005];
void add(int u, int v, ll w) {
  edge[cnt].to = v;
  edge[cnt].val = w;
  edge[cnt].nex = head[u];
  head[u] = cnt++;
}
int main() {
  scanf("%d%d", &n, &m);
  scanf("%d%d", &x, &y);
  memset(head, -1, sizeof(head));
  for (int i = 1; i <= m; i++) {
    int x, y;
    ll z;
    scanf("%d%d%lld", &x, &y, &z);
    add(x, y, z);
    add(y, x, z);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", &e[i].first, &e[i].second);
  }
  for (int i = 0; i <= n; i++) {
    dp[i] = 100000000000000000ll;
  }
  vis[x] = 1;
  dp[x] = 0;
  while (1) {
    int now = -1;
    for (int i = 1; i <= n; i++) {
      if (vis[i] == 1) {
        if (now == -1)
          now = i;
        else {
          if (dp[now] + e[now].second > dp[i] + e[i].second)
            now = i;
        }
      }
    }
    if (now == -1)
      break;
    vis[now] = 2;
    solve(now);
    for (int i = 1; i <= n; i++) {
      if (i == now || vis[i] == 2)
        continue;
      if (dis[i] == dis[0] || dis[i] > e[now].first)
        continue;
      dp[i] = min(dp[i], dp[now] + e[now].second);
      vis[i] = 1;
    }
  }
  printf("%lld\n", dp[y] == dp[0] ? -1ll : dp[y]);
  return 0;
}