// Problem: CF 1648 F - Two Avenues
// https://codeforces.com/contest/1648/problem/F
//
// Algorithm Overview:
// - Goal: Select two edges from a graph such that the number of paths (queries)
// passing through
//   exactly one of them is maximized.
// - Key Techniques:
//   1. Build spanning tree via DFS; back edges (non-tree edges) form
//   fundamental cycles.
//   2. Assign random XOR hash to each back edge; use XOR basis to uniquely
//   identify independent cycles.
//   3. For each fundamental cycle (back edge), check all pairs of edges (same
//   cycle, or different cycles).
//   4. For each pair, compute the count of paths passing through exactly one
//   edge using LCA + persistent segment tree.
//   5. Use divide-and-conquer optimization to reduce time complexity for
//   single-cycle case.
// - Data Structures:
//   - Sparse Table (ST_table): O(1) LCA queries on spanning tree.
//   - Persistent Segment Tree (segt): Count query endpoints in range [L, R] per
//   DFS in-order traversal.
//   - XOR Basis (bas): Map back edges to independent cycles via random hashes.
// - Time Complexity: O((n + k) * polylog) per test case.

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN = 5e5 + 5;
bool Mbe;
int n, m, k;
int eu[MAXN], ev[MAXN], pu[MAXN], pv[MAXN], rt[MAXN];
bool it[MAXN], mark[MAXN], debug;
vector<int> edg[MAXN], son[MAXN], ad[MAXN];
map<ll, int> bas;
map<ll, vector<int>> vec;
int lg[MAXN << 1];
int dep[MAXN], in[MAXN], out[MAXN], tot;
ll hs[MAXN], pat[MAXN];
int ans, ans1, ans2;
int mx1, mx2, id1, id2;
// Sparse Table for LCA (Lowest Common Ancestor) queries on spanning tree.
struct ST_table {
  int a[25][MAXN << 1];
  int chk(int x, int y) {
    return dep[x] < dep[y] ? x : y;
  } // Return shallower node (smaller depth).
  void build() {
    // Precompute sparse table: a[i][j] = ancestor of j after jumping 2^i edges
    // upward on Euler tour.
    for (int i = 1; i < 25; i++)
      for (int j = 1; j + (1 << i) - 1 <= tot; j++)
        a[i][j] = chk(a[i - 1][j], a[i - 1][j + (1 << i - 1)]);
  }
  // Binary lifting on Euler tour: find LCA by range minimum query on depths.
  int lca(int x, int y) {
    x = in[x], y = in[y];
    // Retrieve Euler tour indices for both nodes.
    if (x > y)
      swap(x, y);
    // Query range [x, y] on Euler tour: find minimum depth node using sparse
    // table.
    int k = lg[y - x + 1];
    return chk(a[k][x], a[k][y - (1 << k) + 1]);
  }
} tr;

// Persistent Segment Tree: store count of query endpoints added at each DFS
// in-time.
struct segt {
  // For each DFS in-order position, maintain a versioned tree to query endpoint
  // counts in any range.
  int ls[MAXN * 30], rs[MAXN * 30], sum[MAXN * 30], tot;
  void init() {
    // Reset all nodes; tot counts the number of persistent tree nodes created.
    for (int i = 1; i <= tot; i++)
      ls[i] = rs[i] = sum[i] = 0;
    tot = 0;
    return;
  }
  // Add value x to persistent tree at version id; create new node by copying
  // parent.
  void add(int &id, int x, int l = 1, int r = n) {
    ++tot, ls[tot] = ls[id], rs[tot] = rs[id], sum[tot] = sum[id], id = tot;
    // Increment count at leaf; propagate up the tree.
    sum[id]++;
    if (l == r)
      return;
    int mid = l + r >> 1;
    if (x <= mid)
      add(ls[id], x, l, mid);
    else
      add(rs[id], x, mid + 1, r);
  }
  // Range query on persistent tree id: count endpoints in range [L, R].
  int ask(int id, int L, int R, int l = 1, int r = n) {
    if (L > R)
      return 0;
    if (L <= l && r <= R)
      return sum[id];
    int mid = l + r >> 1;
    if (R <= mid)
      return ask(ls[id], L, R, l, mid);
    if (mid < L)
      return ask(rs[id], L, R, mid + 1, r);
    return ask(ls[id], L, R, l, mid) + ask(rs[id], L, R, mid + 1, r);
  }
} T;
bool Med;

// Build spanning tree using DFS; assign depth and in-time (Euler tour index) to
// each node.
void dfs(int u, int fe) {
  in[u] = ++tot;
  tr.a[0][tot] = u;
  // Mark DFS in-time; initialize sparse table base case for LCA.
  for (int e : edg[u])
    if (e != fe) {
      int v = eu[e] ^ ev[e] ^ u;
      // Retrieve other endpoint via XOR trick.
      if (!in[v]) {
        // Tree edge: recursively build subtree; mark as tree edge.
        son[u].push_back(e);
        dep[v] = dep[u] + 1;
        mark[e] = true;
        dfs(v, e);
        tr.a[0][++tot] = u;
        // Backtrack in Euler tour; prepare for next sibling or parent.
      }
    }
}

// DFS on spanning tree: compute XOR hashes for each subtree; identify max paths
// for single-cycle cases.
void dfs1(int u, int fe) {
  in[u] = ++tot;
  // Euler in-time for persistent segment tree queries.
  for (int e : son[u]) {
    int v = eu[e] ^ ev[e] ^ u;
    dfs1(v, e);
    hs[u] ^= hs[v], pat[u] += pat[v];
    // Accumulate XOR hashes; sum path counts in subtree.
  }
  // If hs[u]==0 (no back edges below u), update max path pair within this
  // component.
  if (hs[u] == 0) {
    if (pat[u] > mx1)
      mx2 = mx1, id2 = id1, mx1 = pat[u], id1 = fe;
    else if (pat[u] > mx2)
      mx2 = pat[u], id2 = fe;
  } else if (bas.count(hs[u])) {
    // XOR hash matches a previous back edge: attempt pairing different cycles.
    if (ans < pat[u])
      ans = pat[u], ans1 = fe, ans2 = bas[hs[u]];
  }
  if (hs[u])
    vec[hs[u]].push_back(fe);
  // Group edges by their cycle (identified by XOR hash).
  out[u] = tot;
  // Mark Euler out-time for range queries.
}

// Divide-and-conquer optimization for pairs within a single cycle.
void solve(vector<int> e) {
  // Lambda: compute path count passing through exactly one of edges ox and oy.
  auto f = [&](int x, int y) {
    int ox = x, oy = y;
    x = ev[x], y = ev[y];
    // Retrieve query endpoints (ev[e] = higher DFS endpoint of back edge e).
    // Count queries with one endpoint inside subtree of x, other outside
    // subtree of y.
    int sm = T.ask(rt[in[x] - 1], in[y], out[y]) +
             T.ask(rt[out[y]], out[x] + 1, n) -
             T.ask(rt[in[y] - 1], out[x] + 1, n);
    // Compute: (paths through x) + (paths through y) - 2*(paths through both).
    int r = pat[x] + pat[y] - 2 * sm;
    if (r > ans)
      ans = r, ans1 = ox, ans2 = oy;
    return r;
  };
  // Divide-and-conquer: for each mid, find best pair (mid, i) where i < mid or
  // i > mid.
  int p = e.size();
  auto sol = [&](auto self, int l, int r, int L, int R) -> void {
    if (l > r)
      return;
    int mid = l + r >> 1, best = 0, maxx = -1;
    // For mid-th edge, find best pairing in range [L, R], preferring indices <
    // mid.
    for (int i = L; i <= R; i++)
      if (mid > i)
        if (maxx < f(e[mid], e[i]))
          best = i, maxx = f(e[mid], e[i]);
    self(self, l, mid - 1, L, best);
    self(self, mid + 1, r, best, R);
    // Recurse on left and right halves with updated search ranges.
  };
  sol(sol, 0, p - 1, 0, p - 1);
  return;
}

// Main solve routine: read graph, compute spanning tree, assign cycle hashes,
// process queries.
void solve(int Tid) {
  cin >> n >> m;
  // Clear graph, spanning tree, XOR basis, and query storage from previous
  // test.
  for (int i = 1; i <= n; i++)
    edg[i].clear(), son[i].clear(), ad[i].clear(), in[i] = false,
                                                   hs[i] = pat[i] = 0;
  for (int i = 1; i <= m; i++)
    it[i] = mark[i] = false;
  tot = 0;
  bas.clear();
  vec.clear();
  ans = mx1 = mx2 = 0;
  ans1 = id1 = 1, ans2 = id2 = 2;
  T.init();
  for (int i = 1; i <= m; i++) {
    cin >> eu[i] >> ev[i];
    edg[eu[i]].push_back(i);
    edg[ev[i]].push_back(i);
  }
  // Build adjacency list.
  dfs(1, 0);
  // Build spanning tree; compute Euler tour for LCA.
  tr.build();
  // Precompute sparse table for O(1) LCA queries.
  for (int i = 1; i <= m; i++)
    if (dep[eu[i]] > dep[ev[i]])
      swap(eu[i], ev[i]);
  // Normalize: eu[i] has smaller depth (closer to root).
  for (int i = 1; i <= m; i++)
    if (!mark[i]) {
      // Back edge: assign random XOR hash; store in basis for cycle
      // identification.
      ll x = ((ll)rnd() << 30) ^ rnd();
      hs[eu[i]] ^= x;
      hs[ev[i]] ^= x;
      bas[x] = i;
    }
  cin >> k;
  // Read k path queries.
  for (int i = 1; i <= k; i++) {
    cin >> pu[i] >> pv[i];
    if (in[pu[i]] > in[pv[i]])
      swap(pu[i], pv[i]);
    // Normalize: pu[i] has earlier DFS in-time.
    // Compute path count delta: +1 at endpoints, -2 at LCA.
    pat[pu[i]]++;
    pat[pv[i]]++;
    pat[tr.lca(pu[i], pv[i])] -= 2;
  }
  tot = 0;
  dfs1(1, 0);
  // DFS on spanning tree: compute cycle hashes, aggregate path counts, track
  // best single-cycle pair.
  for (int i = 1; i <= k; i++)
    ad[in[pu[i]]].push_back(in[pv[i]]);
  // Build persistent segment tree versions: at each DFS in-time, add query
  // endpoints.
  for (int i = 1; i <= n; i++) {
    rt[i] = rt[i - 1];
    for (int x : ad[i])
      T.add(rt[i], x);
  }
  // For each cycle (identified by XOR hash), apply divide-and-conquer to find
  // best pair.
  for (auto i : vec)
    solve(i.second);
  if (ans < mx1 + mx2)
    ans = mx1 + mx2, ans1 = id1, ans2 = id2;
  // Check if pairing two edges from separate trees is better than multi-cycle
  // pairing.
  if (ans1 == ans2)
    ans2 = (ans1 == 1 ? 2 : 1);
  // Ensure two distinct edges are selected (fallback to any two edges if
  // needed).
  cout << ans << endl
       << eu[ans1] << ' ' << ev[ans1] << endl
       << eu[ans2] << ' ' << ev[ans2] << endl;
  // Output max path count and the two selected edges.
}

int main() {
  ios::sync_with_stdio(false);
  cerr << "Memory: " << (&Mbe - &Med) * 1.0 / 1024 / 1024 << endl;
  // Precompute log table for sparse table range queries.
  for (int i = 2; i < (MAXN << 1); i++)
    lg[i] = lg[i >> 1] + 1;
  int _;
  cin >> _;
  // Process multiple test cases.
  for (int i = 1; i <= _; i++)
    solve(i);
}

// https://github.com/VaHiX/CodeForces/