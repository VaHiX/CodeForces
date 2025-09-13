/*
 * Problem URL : https://codeforces.com/contest/2038/problem/H
 * Submit Date : 2025-09-05
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 3005, maxm = 2e4 + 5, inf = 1e9;
int m, n, s, t;
int p[55], mx[55], pos[55], a[55][55];
namespace flow {
int s, t, mxf, mnc, tot = 1;
int head[maxn], to[maxm], f[maxm], val[maxm], nxt[maxm];
int d[maxn], mn[maxn], pre[maxn];
bool vis[maxn];
int all, h[maxn];
void addedge(int u, int v, int c, int w) {
  nxt[++tot] = head[u], to[tot] = v, f[tot] = c, val[tot] = w, head[u] = tot;
  nxt[++tot] = head[v], to[tot] = u, f[tot] = 0, val[tot] = -w, head[v] = tot;
}
void add(int u, int v, int l, int r, int w) {
  addedge(u, v, r - l, w), h[u] -= l, h[v] += l, mnc += l * w;
}
bool spfa() {
  queue<int> q;
  memset(d, 0xcf, sizeof(d));
  memset(mn, 0, sizeof(mn));
  d[s] = 0, mn[s] = inf, q.push(s);
  while (!q.empty()) {
    int u = q.front();
    vis[u] = 0, q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i], w = val[i];
      if (f[i] && d[v] < d[u] + w) {
        d[v] = d[u] + w, mn[v] = min(mn[u], f[i]), pre[v] = i;
        if (!vis[v])
          vis[v] = 1, q.push(v);
      }
    }
  }
  return mn[t];
}
int ek() {
  addedge(::t, ::s, inf, 0);
  for (int i = 1; i < t; i++)
    h[i] > 0 ? all += h[i], addedge(s, i, h[i], 0) : addedge(i, t, -h[i], 0);
  while (spfa()) {
    mxf += mn[t], mnc += d[t] * mn[t];
    for (int i = t; i != s; i = to[pre[i] ^ 1])
      f[pre[i]] -= mn[t], f[pre[i] ^ 1] += mn[t];
  }
  return mxf == all ? mnc : -1;
}
} // namespace flow
int id(int x, int y) { return (x - 1) * n + y; }
int main() {
  scanf("%d%d", &n, &m);
  for (int j = 1; j <= m; j++)
    scanf("%d", &p[j]), mx[j] = mx[j - 1] + (p[j] > p[j - 1]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &a[i][j]);
  s = n * m + m + 1, t = s + 1, flow::s = 0, flow::t = t + 1;
  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n; i++)
      flow::add(id(j, i), j != m ? id(j + 1, i) : t, i == p[j] ? mx[j] : 0,
                mx[j] - (i < p[j]), 0);
    flow::add(s, n * m + j, 1, 1, 0), pos[j] = flow::tot;
    for (int i = 1; i <= n; i++)
      flow::add(n * m + j, id(j, i), 0, 1, a[i][j]);
  }
  if (flow::ek() == -1)
    printf("-1\n"), exit(0);
  for (int j = 1; j <= m; j++)
    for (int i = 1; i <= n; i++)
      if (flow::f[pos[j] + 2 * i])
        printf("%d%c", i, " \n"[j == m]);
  return 0;
}