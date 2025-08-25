/*
 * Problem URL : https://codeforces.com/problemset/problem/2132/F
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
#define pii pair<int, int>
#define f first
#define s second

using namespace std;

const int N = 2e5 + 50, INF = 0x3f3f3f3f;
int n, m, head[N], cnt, dfn[N], low[N], idx, last[N];
bool tag[N << 1];
pii dis[N];
struct E {
  int next, to;
} e[N << 1];
inline void add(int x, int y) {
  e[++cnt] = (E){head[x], y};
  head[x] = cnt;
  tag[cnt] = 0;
}
inline void dfs(int now, int id) {
  dfn[now] = low[now] = ++idx;
  for (int i = head[now]; i; i = e[i].next) {
    if (((i ^ 1) == id))
      continue;
    if (!dfn[e[i].to]) {
      dfs(e[i].to, i);
      low[now] = min(low[now], low[e[i].to]);
      if (low[e[i].to] > dfn[now])
        tag[i] = 1, tag[i ^ 1] = 1;
    } else
      low[now] = min(low[now], dfn[e[i].to]);
  }
}
inline void solve() {
  cin >> n >> m;
  cnt = 1;
  idx = 0;
  for (int i = 1; i <= n; i++)
    head[i] = 0, dfn[i] = 0, low[i] = 0, dis[i].f = INF, dis[i].s = -1,
    last[i] = -1;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dfs(1, 0);
  queue<int> q;
  q.push(1);
  last[1] = 0;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int i = head[now]; i; i = e[i].next) {
      if (last[e[i].to] != -1)
        continue;
      last[e[i].to] = i;
      q.push(e[i].to);
    }
  }
  int now = n;
  while (now != 1) {
    int id = last[now];
    if (tag[id]) {
      dis[now] = min(dis[now], {0, id / 2});
      dis[e[id ^ 1].to] = min(dis[e[id ^ 1].to], {0, id / 2});
    }
    now = e[id ^ 1].to;
  }
  for (int i = 1; i <= n; i++)
    if (dis[i].f == 0)
      q.push(i);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    auto [step, id] = dis[now];
    for (int i = head[now]; i; i = e[i].next) {
      if (dis[e[i].to] > make_pair(step + 1, id)) {
        dis[e[i].to] = {step + 1, id};
        q.push(e[i].to);
      }
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int c;
    cin >> c;
    cout << dis[c].s << ' ';
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}