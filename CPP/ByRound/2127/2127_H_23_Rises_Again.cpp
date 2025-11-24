// Problem: CF 2127 H - 23 Rises Again
// https://codeforces.com/contest/2127/problem/H

/*
 * Problem: H. 23 Rises Again
 * Purpose: Find the maximum number of edges in a subgraph of G that forms a "candy" graph,
 *          where each vertex has degree at most 2.
 * Algorithm: This solution uses a reduction to the problem of finding a maximum matching in a derived graph,
 *            followed by a greedy assignment to determine which edges can be included in a candy subgraph.
 * Time Complexity: O(n^3) due to the Blossom algorithm used for matching (specifically, the implementation
 *                   is tailored for this specific structure). This approach assumes that the number of vertices
 *                   is small (up to 30), and thus, polynomial complexity is acceptable.
 * Space Complexity: O(n^2) for storing the adjacency lists, matching structure, etc.
 */

#include <stdint.h>
#include <iostream>

using namespace std;
#define I_love_you_Liny cin.tie(0)->sync_with_stdio(0)
#define int long long int
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
const long long inf = 3e18;
const int mod = 1e9 + 7;
const int N = 3e5 + 7;
const int MV = 2100;
const int ME = 20000;
int n, m;
int uu[600], vv[600];       // Stores edges
int hd[MV], to_[ME], nx[ME], ec;  // Adjacency list representation (used in blossom algorithm)
int mt[MV], pr[MV], ba[MV], qv[MV];  // Matching and auxiliary arrays for the blossom algorithm
int us[MV], bl[MV], mk[MV];  // Used tracking arrays
int tot;
void clr(int vn) {
  for (int i = 1; i <= vn; i++) {
    hd[i] = -1;
    mt[i] = 0;
    pr[i] = 0;
    ba[i] = i;
    us[i] = 0;
    bl[i] = 0;
    mk[i] = 0;
  }
  ec = 0;
}
void ad(int u, int v) {
  to_[ec] = v;
  nx[ec] = hd[u];
  hd[u] = ec++;
  to_[ec] = u;
  nx[ec] = hd[v];
  hd[v] = ec++;
}
int idc(int v, int k) { return (v - 1) * 2 + k + 1; }  // Maps a vertex to two dummy nodes
int ida(int i) { return 2 * n + 2 * (i - 1) + 1; }     // Unique ID for edge i's first node
int idb(int i) { return 2 * n + 2 * (i - 1) + 2; }     // Unique ID for edge i's second node
int lca(int a, int b) {
  for (int i = 1; i <= tot; i++)
    mk[i] = 0;
  for (;;) {
    a = ba[a];
    mk[a] = 1;
    if (mt[a] == 0)
      break;
    a = pr[mt[a]];
  }
  for (;;) {
    b = ba[b];
    if (mk[b])
      return b;
    if (mt[b] == 0)
      break;
    b = pr[mt[b]];
  }
  return 1;
}
void markp(int v, int b, int x) {
  while (ba[v] != b) {
    bl[ba[v]] = 1;
    bl[ba[mt[v]]] = 1;
    pr[v] = x;
    x = mt[v];
    v = pr[mt[v]];
  }
}
int bfs(int r) {
  for (int i = 1; i <= tot; i++) {
    us[i] = 0;
    pr[i] = 0;
    ba[i] = i;
  }
  int qh = 0, qt = 0;
  qv[qt++] = r;
  us[r] = 1;
  while (qh < qt) {
    int v = qv[qh++];
    for (int e = hd[v]; e != -1; e = nx[e]) {
      int u = to_[e];
      if (ba[v] == ba[u] || mt[v] == u)
        continue;
      if (u == r || (mt[u] != 0 && pr[mt[u]] != 0)) {
        // Found an odd cycle, perform blossom contraction
        int b = lca(v, u);
        for (int i = 1; i <= tot; i++)
          bl[i] = 0;
        markp(v, b, u);
        markp(u, b, v);
        for (int i = 1; i <= tot; i++) {
          if (bl[ba[i]]) {
            ba[i] = b;
            if (!us[i]) {
              us[i] = 1;
              qv[qt++] = i;
            }
          }
        }
      } else if (pr[u] == 0) {
        // Found augmenting path to an unmatched node
        pr[u] = v;
        if (mt[u] == 0)
          return u;
        int w = mt[u];
        if (!us[w]) {
          us[w] = 1;
          qv[qt++] = w;
        }
      }
    }
  }
  return 0;
}
void aug(int v) {
  while (v) {
    int pv = pr[v], nv = mt[pv];
    mt[v] = pv;
    mt[pv] = v;
    v = nv;
  }
}
int mm(int vn) {
  int res = 0;
  for (int i = 1; i <= vn; i++) {
    if (mt[i] == 0) {
      int v = bfs(i);
      if (v) {
        aug(v);
        res++;
      }
    }
  }
  return res;
}
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    uu[i] = a;
    vv[i] = b;
  }
  tot = 2 * n + 2 * m; // Total number of nodes in constructed graph
  clr(tot);
  for (int i = 1; i <= m; i++) {
    int u = uu[i], v = vv[i];
    int a = ida(i), b = idb(i);  // Edge dummy node IDs
    ad(a, b);
    ad(a, idc(u, 0));  // Connect to first endpoint (vertex u)
    ad(a, idc(u, 1));
    ad(b, idc(v, 0));  // Connect to second endpoint (vertex v)
    ad(b, idc(v, 1));
  }
  mm(tot); // Perform maximum matching
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    int u = uu[i], v = vv[i];
    int a = ida(i), b = idb(i);
    int mu = mt[a], mv = mt[b]; // Match in the constructed graph
    int u0 = idc(u, 0), u1 = idc(u, 1);  // Vertex u's dummy nodes
    int v0 = idc(v, 0), v1 = idc(v, 1);
    int ok1 = (mu == u0 || mu == u1);  // Check if edge i is "used"
    int ok2 = (mv == v0 || mv == v1);
    if (ok1 && ok2)
      ans++; // If both endpoints were matched properly, include the edge
  }
  cout << ans << '\n';
}
int32_t main() {
  I_love_you_Liny;
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/