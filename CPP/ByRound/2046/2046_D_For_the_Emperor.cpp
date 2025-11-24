// Problem: CF 2046 D - For the Emperor!
// https://codeforces.com/contest/2046/problem/D

/*
D. For the Emperor!
Algorithm: Strongly Connected Components + Minimum Cost Maximum Flow

This problem models a directed graph where each node has some number of messengers,
and we want to determine the minimum number of plans that need to be initially given
to messengers such that every city receives at least one plan via message propagation.
The solution uses:
1. Tarjan's algorithm to find strongly connected components (SCCs),
2. Then builds a flow network on the condensed graph,
3. Uses minimum cost maximum flow (SPFA-based) to solve the assignment.

Time Complexity: O((n + m)^2 * max_flow) which is acceptable given constraints.
Space Complexity: O(n + m)
*/

#include <algorithm>
#include <queue>
#include <stdio.h>
#include <utility>
#include <vector>
#define N 1005
#define M 10005
using namespace std;
const int inf = 1e9;
int n, m, s, t, k;
int h[N], to[M], nxt[M], w[M], c[M], cnt;
void jb(int u, int v, int W, int C) {
  to[++cnt] = v;
  w[cnt] = W;
  c[cnt] = C;
  nxt[cnt] = h[u];
  h[u] = cnt;
}
void JB(int u, int v, int W, int C) {
  jb(u, v, W, C);
  jb(v, u, 0, -C); // Reverse edge with negative cost
}
int dis[N], fl[N], lst[N];
bool vis[N];
queue<int> Q;
bool spfa() {
  for (int i = 1; i <= k; i++)
    dis[i] = inf, lst[i] = 0, vis[i] = 0;
  dis[s] = 0;
  fl[s] = inf;
  Q.push(s);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    vis[u] = 0;
    for (int i = h[u]; i != 0; i = nxt[i]) {
      int v = to[i];
      if (w[i] > 0 && dis[v] > dis[u] + c[i]) { // Relax edge
        dis[v] = dis[u] + c[i];
        fl[v] = min(fl[u], w[i]);
        lst[v] = i;
        if (vis[v] == 0) {
          vis[v] = 1;
          Q.push(v);
        }
      }
    }
  }
  return lst[t] != 0; // If path found to sink
}
pair<int, int> work() {
  int res = 0, ct = 0;
  while (spfa()) { // Augment paths until no more available
    res += dis[t] * fl[t];
    ct += fl[t];
    for (int i = t; i != s; i = to[lst[i] ^ 1]) { // Update residual capacities along path
      w[lst[i]] -= fl[t];
      w[lst[i] ^ 1] += fl[t];
    }
  }
  return make_pair(res, ct);
}
int a[N], sa[N];
int dfn[N], low[N], tot, bel[N], sc;
int st[N], hd;
vector<int> vec[N];
void tarjan(int u) {
  st[++hd] = u; // Push node on stack
  low[u] = dfn[u] = ++tot;
  for (int v : vec[u]) {
    if (!dfn[v]) {
      tarjan(v); // DFS traversal
      low[u] = min(low[u], low[v]);
    } else if (!bel[v])
      low[u] = min(low[u], dfn[v]); // Back edge found, update low
  }
  if (low[u] == dfn[u]) { // Root of SCC
    sc++;
    while (1) {
      int x = st[hd];
      hd--;
      bel[x] = sc; // Assign component ID to node
      if (x == u)
        break;
    }
  }
}
void solve() {
  cnt = 1;
  hd = tot = sc = 0;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    vec[u].push_back(v); // Build adjacency list
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i])
      tarjan(i); // Find SCCs
  t = k = 2 * sc + 2;
  s = k - 1;
  for (int i = 1; i <= sc; i++)
    sa[i] = 0;
  for (int i = 1; i <= n; i++) {
    sa[bel[i]] += a[i]; // Accumulate messenger count per SCC
    for (int v : vec[i]) {
      if (bel[i] != bel[v])
        JB(bel[i] + sc, bel[v], inf, 0); // Connect different components with infinite capacity and zero cost
    }
  }
  for (int i = 1; i <= sc; i++) {
    JB(s, i + sc, sa[i] + 1, 0); // Source to super node with supply = sum of messengers plus one
    JB(i, i + sc, inf, 0);       // Self-loop in component with unlimited capacity and zero cost
    if (sa[i] > 0)
      JB(i + sc, i, 1, 1);       // If there are messengers, allow one plan transfer back for free
    JB(i, t, 1, 0);              // Component to sink to capture one message per component
  }
  pair<int, int> ans = work();   // Run min-cost max-flow
  if (ans.second != sc)          // Not enough messengers to cover all SCCs?
    printf("-1\n");
  else
    printf("%d\n", ans.first);
  for (int i = 1; i <= n; i++)
    vec[i].clear(), dfn[i] = bel[i] = 0; // Reset for next case
  for (int i = 1; i <= k; i++)
    h[i] = 0;
  for (int i = 1; i <= sc; i++)
    sa[i] = 0;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/