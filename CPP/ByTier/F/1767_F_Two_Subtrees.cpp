// Problem: CF 1767 F - Two Subtrees
// https://codeforces.com/contest/1767/problem/F

/*
Algorithm/Techniques: 
- Mo's Algorithm on Tree with offline queries
- Heavy-light decomposition or block-based optimization with sqrt decomposition
- Tree DFS traversal to assign dfn numbers and subtree sizes
- Efficient insertion/deletion of elements in blocks to track frequency and maximum frequency
- Two-level block structure for efficient processing of queries

Time Complexity: O((n + q) * sqrt(n) * sqrt(n)) ~ O(n * q) in worst case, but with optimizations it's much better
Space Complexity: O(n * sqrt(n)) for the block structures and auxiliary arrays
*/

#include <ctype.h>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N = 2e5 + 5, M = 7000, B = 550;
struct edge {
  int v, nx;
} e[N << 1];
struct Query {
  int l, r, u, v, id;
} q[N];
int n, m, ne, tot, f[N], a[N], b1[N], b2[N], sz[N], dfn[N], rev[N];
int ans[N], cnt[N], mx[370], s[370][N];
int read() {
  int s = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    s = s * 10 + ch - '0';
    ch = getchar();
  }
  return s * f;
}
void read(int u, int v) {
  e[++ne].v = v;
  e[ne].nx = f[u];
  f[u] = ne;
}
void dfs(int u, int ffa) {
  dfn[++tot] = a[u], rev[u] = tot, sz[u] = 1;
  for (int i = f[u]; i; i = e[i].nx) {
    int v = e[i].v;
    if (v == ffa)
      continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
}
bool cmp(Query x, Query y) {
  if (b1[x.l] != b1[y.l])
    return b1[x.l] < b1[y.l];
  if (b1[x.r] != b1[y.r])
    return b1[x.r] < b1[y.r];
  return (b1[x.u] != b1[y.u]) ? (b1[x.u] < b1[y.u]) : (x.v < y.v);
}
void add(int x) {
  s[b2[x]][cnt[x]]--, cnt[x]++, s[b2[x]][cnt[x]]++;
  if (s[b2[x]][mx[b2[x]] + 1])
    mx[b2[x]]++;
}
void del(int x) {
  s[b2[x]][cnt[x]]--, cnt[x]--, s[b2[x]][cnt[x]]++;
  if (!s[b2[x]][mx[b2[x]]])
    mx[b2[x]]--;
}
int main() {
  n = read();
  for (int i = 1; i <= n; i++)
    a[i] = read();
  for (int i = 1; i <= N - 5; i++)
    b1[i] = (i - 1) / M + 1, b2[i] = (i - 1) / B + 1;
  for (int i = 1, u, v; i < n; i++) {
    u = read(), v = read();
    read(u, v), read(v, u);
  }
  dfs(1, 0);
  m = read();
  for (int i = 1, x, y; i <= m; i++) {
    x = read(), y = read();
    q[i] = (Query){rev[x], rev[x] + sz[x] - 1, rev[y], rev[y] + sz[y] - 1, i};
  }
  sort(q + 1, q + 1 + m, cmp);
  int l = 1, r = 0, u = 1, v = 0;
  for (int i = 1; i <= m; i++) {
    while (l > q[i].l)
      add(dfn[--l]);
    while (l < q[i].l)
      del(dfn[l++]);
    while (u > q[i].u)
      add(dfn[--u]);
    while (u < q[i].u)
      del(dfn[u++]);
    while (r < q[i].r)
      add(dfn[++r]);
    while (r > q[i].r)
      del(dfn[r--]);
    while (v < q[i].v)
      add(dfn[++v]);
    while (v > q[i].v)
      del(dfn[v--]);
    int x = 0, y = 0;
    for (int j = 1; j <= 364; j++)
      if (mx[j] > x)
        x = mx[j], y = j;
    for (int j = 1, mn = (y - 1) * B; j <= B; j++) {
      mn++;
      if (cnt[mn] == x) {
        ans[q[i].id] = mn;
        break;
      }
    }
  }
  for (int i = 1; i <= m; i++)
    printf("%d\n", ans[i]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/