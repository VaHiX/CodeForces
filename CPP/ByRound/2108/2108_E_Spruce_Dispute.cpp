/*
 * Problem URL : https://codeforces.com/problemset/problem/2108/E
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int T, n, head[N], ecnt;
struct Edge {
  int to, nxt;
} e[N << 1];
void addedge(int x, int y) {
  e[++ecnt] = {y, head[x]};
  head[x] = ecnt;
}
int U, V, rt, sz[N], dep[N];
void dfs(int x, int fa) {
  int mx = 0;
  sz[x] = 1;
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dfs(y, x);
    mx = max(sz[y], mx);
    sz[x] += sz[y];
  }
  mx = max(mx, n - sz[x]);
  if (mx <= n / 2)
    rt = x;
}
void dfs1(int x, int fa) {
  sz[x] = 1;
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dep[y] = dep[x] + 1;
    dfs1(y, x);
    sz[x] += sz[y];
  }
}
int dfn[N], d;
void dfs2(int x, int fa) {
  if (x != V)
    dfn[x] = ++d;
  if (d == n / 2)
    d = 0;
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa)
      continue;
    dfs2(y, x);
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ecnt = 0;
    for (int i = 1; i <= n; i++)
      dfn[i] = head[i] = 0;
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      addedge(x, y);
      addedge(y, x);
    }
    dfs(1, 0);
    dep[rt] = 0;
    dfs1(rt, 0);
    int delt = N << 1;
    for (int u = 1; u <= n; u++)
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, _delt;
        if (u > v)
          continue;
        if (dep[u] < dep[v])
          _delt = dep[v] + (sz[v] - 1);
        if (dep[u] > dep[v])
          _delt = sz[u] + dep[v];
        if (_delt < delt)
          U = u, V = v, delt = _delt;
      }
    if (V == rt)
      rt = U;
    d = 0;
    dfs2(rt, 0);
    printf("%d %d\n", U, V);
    for (int i = 1; i <= n; i++)
      printf("%d ", dfn[i]);
  }
  return 0;
}
