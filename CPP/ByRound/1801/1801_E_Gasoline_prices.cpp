// Problem: CF 1801 E - Gasoline prices
// https://codeforces.com/contest/1801/problem/E

/*
Algorithm: 
- This code solves a complex problem on a tree with dynamic connectivity and range queries.
- It uses Heavy-Light Decomposition (HLD) for path queries and Union-Find (Disjoint Set Union) for maintaining connected components.
- The key idea is to process each query (pairs of paths) and merge components based on equality constraints between nodes.
- It uses modular arithmetic to handle large numbers and bit manipulation for efficient operations.
- Time Complexity: O(m * n * log(n)) due to path queries and component merging.
  Space Complexity: O(n * log(n)) for storing HLD and component information.

*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast")
using namespace std;
const int N = 2e5 + 10;
const int mod = 1e9 + 7; // Corrected from 1e9 + 1 to standard mod
const int Q = 2333; // Base for polynomial hashing
struct node {
  int l, r;
} a[N];
int n, x, cnt, y, q, p, m, ans;
vector<int> e[N], nod[N]; // e stores adjacency list, nod stores nodes in each component
int fac[N], dep[N], siz[N], son[N], top[N], dfn[N], id[N], tree[N << 2], fa[N],
    sz[N], inv[N], up[N], g[N], sum;
int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
int dec(int x, int y) { return x < y ? x - y + mod : x - y; }
int mul(int x, int y) { return 1ll * x * y % mod; }
int ksm(int x, int y) { // Fast exponentiation
  int ans = 1;
  for (; y; y >>= 1, x = mul(x, x))
    if (y & 1)
      ans = mul(ans, x);
  return ans;
}
void dfs(int x, int d) {
  dep[x] = d;
  siz[x] = 1;
  son[x] = 0;
  for (int i = 0; i < e[x].size(); i++) {
    int u = e[x][i];
    dfs(u, d + 1);
    siz[x] += siz[u];
    if (siz[son[x]] < siz[u])
      son[x] = u;
  }
}
void dfs1(int x, int t) { // Heavy-light decomposition
  dfn[x] = ++cnt;
  id[cnt] = x;
  top[x] = t;
  if (son[x])
    dfs1(son[x], t);
  for (int i = 0; i < e[x].size(); i++) {
    int u = e[x][i];
    if (u == son[x])
      continue;
    dfs1(u, u);
  }
}
void getpath(int x, int y, vector<pair<int, int>> &q) {
  vector<pair<int, int>> p;
  while (1) {
    if (top[x] == top[y]) {
      q.push_back(make_pair(dfn[x], dfn[y]));
      break;
    } else if (dep[top[x]] <= dep[top[y]]) {
      p.push_back(make_pair(dfn[top[y]], dfn[y]));
      y = up[top[y]];
    } else {
      q.push_back(make_pair(dfn[x], dfn[top[x]]));
      x = up[top[x]];
    }
  }
  for (int i = (int)p.size() - 1; i >= 0; i--)
    q.push_back(p[i]);
}
void put(int x, int y) { // Binary Indexed Tree update
  while (x <= n) {
    tree[x] = add(tree[x], y);
    x += (x & (-x));
  }
}
int get(int x) { // Binary Indexed Tree query
  int ans = 0;
  while (x) {
    ans = add(ans, tree[x]);
    x -= (x & (-x));
  }
  return ans;
}
void build() {
  for (int i = 1; i <= n; i++) {
    put(i, mul(fac[i], id[i])); // Initialization for BIT
    g[i] = id[i];
  }
}
int findans(int ql, int qr) { return dec(get(qr), get(ql - 1)); }
void change(int x, int y) { 
  put(x, mul(fac[x], dec(y, g[x]))); // Update BIT
  g[x] = y;
}
int getfather(int x) { return fa[x] == x ? x : fa[x] = getfather(fa[x]); } // Find root of DSU
void merge(int x, int y) { // Merge two components
  x = getfather(x);
  y = getfather(y);
  if (sz[x] < sz[y])
    swap(x, y);
  if (x != y) {
    fa[y] = x;
    sz[x] += sz[y];
    ans = mul(ans, ksm(max(0, a[x].r - a[x].l + 1), mod - 2));
    ans = mul(ans, ksm(max(0, a[y].r - a[y].l + 1), mod - 2));
    a[x].l = max(a[x].l, a[y].l); // Update range
    a[x].r = min(a[x].r, a[y].r);
    ans = mul(ans, max(0, a[x].r - a[x].l + 1));
    for (int i = 0; i < nod[y].size(); i++) {
      nod[x].push_back(nod[y][i]);
      change(dfn[nod[y][i]], x);
    }
    nod[y].clear();
  }
}
void solve(int x, int y, int p, int q) {
  if (x == y) {
    if (getfather(id[x]) != getfather(id[p]))
      merge(id[x], id[p]);
    return;
  } else if ((getfather(id[x]) == getfather(id[p])) &&
             (mul(findans(min(x, y), max(x, y)), inv[min(x, y)]) ==
              mul(findans(min(p, q), max(p, q)), inv[min(p, q)]))) {
    return;
  } else {
    int mid = abs(x - y) / 2;
    solve(x, x + (y > x ? 1 : -1) * mid, p, p + (q > p ? 1 : -1) * mid);
    solve(x + (y > x ? 1 : -1) * (mid + 1), y, p + (q > p ? 1 : -1) * (mid + 1),
          q);
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &x);
    up[i] = x;
    e[x].push_back(i);
  }
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = mul(fac[i - 1], Q);
  inv[0] = inv[1] = 1;
  inv[1] = ksm(Q, mod - 2);
  for (int i = 2; i <= n; i++)
    inv[i] = mul(inv[1], inv[i - 1]);
  ans = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].l, &a[i].r);
    ans = mul(ans, a[i].r - a[i].l + 1);
  }
  for (int i = 1; i <= n; i++)
    fa[i] = i, sz[i] = 1, nod[i].push_back(i);
  dfs(1, 0);
  dfs1(1, 1);
  build();
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &x, &y, &q, &p);
    vector<pair<int, int>> v, u;
    v.clear();
    u.clear();
    getpath(x, y, v);
    getpath(q, p, u);
    int l = 0, r = 0;
    while (l < v.size() && r < u.size()) {
      int len = min(abs(v[l].second - v[l].first) + 1,
                    abs(u[r].second - u[r].first) + 1);
      solve(v[l].first,
            v[l].first + (v[l].second > v[l].first ? 1 : -1) * (len - 1),
            u[r].first,
            u[r].first + (u[r].second > u[r].first ? 1 : -1) * (len - 1));
      if (abs(v[l].first - v[l].second) + 1 <= len)
        l++;
      else {
        if (v[l].first < v[l].second)
          v[l].first += len;
        else
          v[l].first -= len;
      }
      if (abs(u[r].second - u[r].first) + 1 <= len)
        r++;
      else {
        if (u[r].first < u[r].second)
          u[r].first += len;
        else
          u[r].first -= len;
      }
    }
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/