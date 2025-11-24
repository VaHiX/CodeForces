// Problem: CF 1889 E - Doremy's Swapping Trees
// https://codeforces.com/contest/1889/problem/E

/*
 * Problem: E. Doremy's Swapping Trees
 * 
 * Approach:
 * This problem involves determining the number of distinct trees T1 that can be obtained
 * by swapping certain edge sets between two trees T1 and T2. The key insight is to use 
 * graph operations and find connected components with similar structure to analyze 
 * all possible transformations.
 * 
 * Algorithm:
 * - Build a heavy-light decomposition (HLD) on both trees T1 and T2.
 * - For each node in T1, link it with its corresponding node in T2 using a virtual graph.
 * - Build a segment tree on the HLD traversal.
 * - Use Tarjan's algorithm for finding strongly connected components (SCCs) 
 *   in the resulting virtual graph where edges represent operations.
 * - Count valid (non-trivial) SCCs to determine the number of distinct T1.
 * 
 * Time Complexity: O(n * log(n))
 * Space Complexity: O(n * log(n))
 * 
 * Techniques:
 * - Heavy-Light Decomposition (HLD)
 * - Tarjan's algorithm for finding SCCs
 * - Segment trees with virtual edges
 * - Virtual graph construction for edge swapping model
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;
const int mod = 1e9 + 7;
const int N = 2e5 + 5;
const int M = N * 6;
vector<int> T[N], G[M];
int siz[N], dep[N], top[N], son[N], f[N], rev[N];
int scc[N], stk[M], sz[M], dfn[M], low[M], deg[M];
bool vis[M];
int t, n, tim, cnt, tp;
void dfs(int u) {
  for (auto v : T[u])
    if (v ^ f[u])
      dep[v] = dep[f[v] = u] + (siz[v] = 1), dfs(v), siz[u] += siz[v],
      (siz[v] > siz[son[u]] && (son[u] = v, 1));
}
int pat(int u) { return u + 10 * n; }
void dfs(int u, int tp) {
  top[u] = tp, dfn[u] = ++tim, rev[tim] = u;
  G[pat(u)].push_back(u);
  if (son[u])
    G[pat(son[u])].push_back(pat(u)), dfs(son[u], tp);
  for (auto v : T[u])
    if (v ^ f[u] && v ^ son[u])
      dfs(v, v);
}
void build(int l, int r, int rt) {
  if (l == r)
    return G[rt + 2 * n].push_back(rev[l]), void();
  build(l, mid, ls), build(mid + 1, r, rs);
  G[rt + 2 * n].push_back(ls + 2 * n);
  G[rt + 2 * n].push_back(rs + 2 * n);
}
void connect(int l, int r, int rt, int L, int R, int x) {
  if (L <= l && r <= R)
    return G[x].push_back(rt + 2 * n), void();
  if (L <= mid)
    connect(l, mid, ls, L, R, x);
  if (mid < R)
    connect(mid + 1, r, rs, L, R, x);
}
void connect(int u, int v, int x) {
  while (top[u] ^ top[v]) {
    if (dep[top[u]] < dep[top[v]])
      swap(u, v);
    G[x].push_back(pat(u));
    u = f[top[u]];
  }
  if (dep[u] > dep[v])
    swap(u, v);
  connect(1, n << 1, 1, dfn[u] + 1, dfn[v], x);
}
int val(int u) { return u != 1 && u != n + 1 && u <= 2 * n; }
void tarjan(int u) {
  dfn[u] = low[u] = ++tim;
  vis[stk[++tp] = u] = 1;
  for (auto v : G[u])
    if (!dfn[v])
      tarjan(v), low[u] = min(low[u], low[v]);
    else if (vis[v])
      low[u] = min(low[u], dfn[v]);
  if (low[u] == dfn[u]) {
    scc[u] = ++cnt, sz[cnt] += val(u), vis[u] = false;
    while (stk[tp] ^ u)
      scc[stk[tp]] = cnt, sz[cnt] += val(stk[tp]), vis[stk[tp]] = false, --tp;
    --tp;
  }
}
void solve() {
  cin >> n;
  for (int i = 1, u, v; i < n; ++i)
    cin >> u >> v, T[u].push_back(v), T[v].push_back(u);
  for (int i = 1, u, v; i < n; ++i)
    cin >> u >> v, u += n, v += n, T[u].push_back(v), T[v].push_back(u);
  siz[1] = siz[n + 1] = 1;
  dfs(1), dfs(n + 1);
  dfs(1, 1), dfs(n + 1, n + 1);
  build(1, n << 1, 1);
  for (int i = 2; i <= n; ++i)
    connect(n + i, n + f[i], i), connect(i, f[i + n] - n, n + i);
  for (int i = 1; i <= (n << 1); ++i)
    dfn[i] = 0;
  tim = 0;
  for (int i = 1; i <= n * 12; ++i)
    if (!dfn[i])
      tarjan(i);
  for (int u = 1; u <= n * 12; ++u)
    for (auto v : G[u])
      if (scc[u] ^ scc[v])
        ++deg[scc[u]];
  int ans = 1;
  for (int i = 1; i <= cnt; ++i) {
    if (!sz[i] || (sz[i] == 2 && !deg[i]))
      continue;
    ans = 2ll * ans % mod;
  }
  cout << ans << '\n';
  for (int i = 1; i <= (n << 1); ++i)
    f[i] = son[i] = 0, T[i].clear();
  for (int i = 1; i <= n * 12; ++i)
    G[i].clear(), vis[i] = dfn[i] = low[i] = scc[i] = 0;
  for (int i = 1; i <= cnt; ++i)
    sz[i] = deg[i] = 0;
  tim = cnt = tp = 0;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/