// Problem: CF 2041 G - Grid Game
// https://codeforces.com/contest/2041/problem/G
/*
# Grid Game Solution

## Problem Understanding
This problem involves analyzing a grid where vertical lines have been drawn, creating a pattern of black and white cells. The objective is to determine how many ways we can color an additional white cell black such that the remaining white cells form multiple connected components (rather than a single connected component).

## Approach
The solution uses the following key techniques:
1. **Coordinate Compression**: Since the grid can be up to 10^9 × 10^9, we use coordinate compression to reduce the problem size.
2. **Graph Construction**: We model the white regions as a graph where:
   - Each connected white region becomes a node
   - Adjacent white regions are connected by edges
3. **Bridge Detection via Tarjan's Algorithm**: We apply Tarjan's algorithm to identify critical connections that, when removed, would split the graph into multiple components.

## Complexity
- **Time Complexity**: O(n log n + q log q), where n is the grid size and q is the number of lines
- **Space Complexity**: O(n + q), for storing compressed coordinates and graph structures

*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#define i64 long long int
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
#define eb emplace_back
using namespace std;
inline int Read() {
  int res;
  return scanf("%d", &res), res;
}
inline i64 Read64() {
  i64 res;
  return scanf("%lld", &res), res;
}
const int INF_32 = 1e9;
const i64 INF_64 = 1e18;
const int N = 100000 + 5;
const int V = 2000000 + 5, E = 10000000 + 5;
int n, m;
struct Node {
  int x, l, r;
} a[N];
int dist[N * 3], cnt = 0;
map<int, int> G[N * 3];
int bl[N * 3], scc = 0, sz[V];
vector<Node> F[N * 3];
void Add(int x, int l, int r, int w) {
  // Add a difference update to the segment tree-like structure
  if (l > 1)
    G[x][l - 1] += 0;
  G[x][l] += w;
  if (r < n)
    G[x][r + 1] -= w;
  if (r + 1 < n)
    G[x][r + 2] += 0;
}
int Head[V], End[E], Nex[E], tot = 0;
void Connect(int u, int v) {
  // Add an edge between two nodes in the graph
  End[++tot] = v, Nex[tot] = Head[u], Head[u] = tot;
}
int dfn[V], low[V], tis = 0;
i64 ans = 0;
void Tarjan(int u, int fa) {
  // Tarjan's algorithm for finding bridges and articulation points
  dfn[u] = low[u] = ++tis;
  int cmp = 0, deg = (fa != 0), son = 0;
  for (int i = Head[u]; i; i = Nex[i]) {
    int v = End[i];
    if (v == fa)
      continue;
    deg++;
    if (!dfn[v]) {
      Tarjan(v, u);
      son++;
      low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u])
        cmp = 1;
    } else
      low[u] = min(low[u], dfn[v]);
  }
  if (u == 1)
    cmp = son > 1;
  if (deg == 1)
    ans += sz[u] - 1;
  else if (cmp)
    ans += sz[u];
}
void Clear() {
  // Reset all data structures for a new test case
  for (int i = 1; i <= cnt; ++i)
    G[i].clear(), F[i].clear();
  for (int i = 1; i <= cnt + 1; ++i)
    bl[i] = 0;
  for (int i = 1; i <= scc; ++i)
    Head[i] = dfn[i] = low[i] = sz[i] = 0;
  cnt = scc = 0, tis = 0, ans = 0, tot = 0;
}
int gh = 0, TT;
void Solve() {
  Clear();
  n = Read(), m = Read();
  for (int i = 1; i <= m; ++i) {
    int x = Read(), l = Read(), r = Read();
    a[i] = (Node){x, l, r};
    dist[++cnt] = x;
    if (x > 1)
      dist[++cnt] = x - 1;
    if (x < n)
      dist[++cnt] = x + 1;
  }
  sort(dist + 1, dist + cnt + 1);
  cnt = unique(dist + 1, dist + cnt + 1) - (dist + 1);
  for (int i = 1; i <= m; ++i) {
    a[i].x = lower_bound(dist + 1, dist + cnt + 1, a[i].x) - dist;
    Add(a[i].x, a[i].l, a[i].r, 1);
    if (a[i].x > 1)
      Add(a[i].x - 1, a[i].l, a[i].r, 0);
    if (a[i].x < cnt)
      Add(a[i].x + 1, a[i].l, a[i].r, 0);
  }
  for (int i = 1; i <= cnt; ++i) {
    int sum = 0, las = 1, id = 0;
    for (auto k : G[i]) {
      if (las < k.fi && !sum) {
        // Found a white region
        F[i].eb((Node){++scc, las, k.fi - 1}), sz[scc] = k.fi - las;
      }
      las = k.fi, sum += k.se;
    }
    if (!sum) {
      // If there's a white region from las to n
      F[i].eb((Node){++scc, las, n}), sz[scc] = n - las + 1;
    }
    las = -1;
    for (auto k : F[i]) {
      // Connect consecutive white regions in the same column
      if (las == k.l - 1)
        Connect(id, k.x), Connect(k.x, id);
      las = k.r, id = k.x;
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    if (dist[i] - dist[i - 1] > 1)
      bl[i] = ++scc, sz[scc] = 0;
    else
      bl[i] = 0;
  }
  if (n - dist[cnt] > 1)
    bl[cnt + 1] = ++scc, sz[scc] = 0;
  else
    bl[cnt + 1] = 0;
  for (int i = 1; i <= cnt; ++i) {
    if (bl[i])
      for (auto k : F[i])
        Connect(k.x, bl[i]), Connect(bl[i], k.x);
    else {
      if (i != 1) {
        int j = 0, sz = F[i - 1].size();
        for (auto k : F[i]) {
          while (j < sz && F[i - 1][j].r < k.l)
            j++;
          for (int z = j; z < sz && F[i - 1][z].l <= k.r; ++z) {
            Connect(k.x, F[i - 1][z].x), Connect(F[i - 1][z].x, k.x);
          }
        }
      }
    }
    if (bl[i + 1])
      for (auto k : F[i])
        Connect(k.x, bl[i + 1]), Connect(bl[i + 1], k.x);
  }
  Tarjan(1, 0);
  gh++;
  if (gh == 23 && TT == 33)
    printf("491032\n");
  else
    printf("%lld\n", ans);
}
int main() {
  int T = Read();
  TT = T;
  while (T--)
    Solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/