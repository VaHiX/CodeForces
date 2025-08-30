/*
 * Problem URL : https://codeforces.com/problemset/problem/1765/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1005, B = 300005, INF = 1e9;
char a[N][N];
bitset<N> b[N];
int n, m, id[N], c[N], h[N], tot = 1, s, t, cur[N], d[N], ans, to[N], cc[N],
                             num, be[N], f[N][N];
bool vis[N];
struct edge {
  int to, val, nxt;
} e[B];
void add(int u, int v, int w) {
  e[++tot] = {v, w, h[u]};
  h[u] = tot;
}
void Add(int u, int v, int w) {
  add(u, v, w);
  add(v, u, 0);
}
bool bfs() {
  queue<int> q;
  for (int i = 1; i <= t; i++)
    d[i] = 0;
  q.push(s);
  d[s] = 1;
  cur[s] = h[s];
  while (q.size()) {
    int u = q.front();
    q.pop();
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to, val = e[i].val;
      if (val == 0 || d[v])
        continue;
      d[v] = d[u] + 1;
      cur[v] = h[v];
      q.push(v);
      if (v == t)
        return 1;
    }
  }
  return 0;
}
int dinic(int u, int sum) {
  if (u == t)
    return sum;
  int res = sum;
  for (int &i = cur[u]; i && res; i = e[i].nxt) {
    int v = e[i].to, val = e[i].val;
    if (val == 0 || d[v] != d[u] + 1)
      continue;
    int k = dinic(v, min(res, val));
    if (!k)
      d[v] = 0;
    res -= k;
    e[i].val -= k, e[i ^ 1].val += k;
  }
  return sum - res;
}
int main() {
  scanf("%d%d", &m, &n);
  for (int i = 1; i <= m; i++)
    scanf("%s", a[i] + 1);
  for (int j = 1; j <= n; j++) {
    id[j] = j;
    for (int i = 1; i <= m; i++) {
      if (a[i][j] == '1') {
        c[j]++;
        b[j][i] = 1;
      }
    }
  }
  sort(id + 1, id + n + 1, [](int i, int j) { return c[i] < c[j]; });
  s = n + n + 1, t = s + 1;
  for (int i = 1; i <= n; i++) {
    Add(s, id[i], 1);
    Add(id[i] + n, t, 1);
    for (int j = i + 1; j <= n; j++) {
      if ((b[id[i]] & b[id[j]]) == b[id[i]])
        Add(id[j], id[i] + n, 1);
    }
  }
  while (bfs())
    ans += dinic(s, INF);
  for (int u = 1; u <= n; u++) {
    for (int i = h[u]; i; i = e[i].nxt) {
      int v = e[i].to, val = e[i].val;
      if (v != s && val == 0) {
        to[u] = v - n;
        vis[v - n] = 1;
      }
    }
  }
  for (int u = 1; u <= n; u++) {
    if (!vis[u]) {
      int v = u, cnt = 0;
      num++;
      while (v) {
        be[v] = num;
        cc[v] = ++cnt;
        for (int i = 1; i <= m; i++)
          if (b[v][i])
            f[i][num]++;
        v = to[v];
      }
    }
  }
  printf("%d\n", num);
  for (int i = 1; i <= n; i++)
    printf("%d ", be[i]);
  printf("\n");
  for (int i = 1; i <= n; i++)
    printf("%d ", cc[i] + 1);
  printf("\n");
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= num; j++)
      printf("%d ", f[i][j] + 1);
    printf("\n");
  }
  return 0;
}