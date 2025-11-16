// Problem: CF 1783 G - Weighed Tree Radius
// https://codeforces.com/contest/1783/problem/G

/*
 * Problem: G. Weighed Tree Radius
 * 
 * Purpose: 
 *   This code efficiently handles dynamic updates to vertex weights in a tree
 *   and computes the radius of the tree after each update.
 *   
 *   The radius is defined as the minimum eccentricity among all vertices,
 *   where eccentricity of a vertex is the maximum weighted distance from it
 *   to any other vertex in the tree.
 *   
 *   Each weighted distance w_v(u) is defined as d_v(u) + a_u, where d_v(u) 
 *   is the number of edges between v and u, and a_u is the weight of vertex u.
 *   
 * Algorithms/Techniques:
 *   - Tree DFS traversal with Euler tour technique
 *   - Segment tree with node information for subtree queries
 *   - Dynamic updates with propagation
 *   
 * Time Complexity: O(n log n + m log n)
 * Space Complexity: O(n)
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, r, l) for (int i = (r); i >= (l); i--)
#define mem(a, b) memset(a, b, sizeof a)
#define For(i, l, r) for (int i = (l), i##e = (r); i < i##e; i++)
#define pb push_back
#define eb emplace_back
using namespace std;
const int N = 2e5 + 8, M = 1 << 18;
int n, m, a[N], idx, dfn[N], dep[N], c[M << 1][6];
vector<int> G[N];

// DFS to build Euler tour and initialize segment tree
void dfs(int u, int f, int d) {
  dfn[u] = ++idx, dep[idx] = d;
  // Initialize segment tree nodes with values for subtree
  c[M + idx][0] = -d * 2;
  c[M + idx][1] = a[u];
  c[M + idx][2] = d + a[u];
  c[M + idx][4] = a[u] - d;
  for (int v : G[u])
    if (v != f)
      dfs(v, u, d + 1);
}

// Push up operation to update parent node based on children
inline void pu(int i) {
  int l = i * 2, r = i * 2 + 1;
  c[i][1] = max(c[l][1], c[r][1]);
  c[i][2] = max(c[l][2], c[r][2]);
  c[i][3] = max({c[l][3], c[r][3], c[l][2] + c[r][0]});
  c[i][4] = max({c[l][4], c[r][4], c[l][0] + c[r][2]});
  c[i][5] = max({c[l][5], c[r][5], c[l][2] + c[r][4], c[l][3] + c[r][2]});
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  rep(i, 1, n) cin >> a[i];
  int u, v;
  rep(i, 2, n) cin >> u >> v, G[u].pb(v), G[v].pb(u);
  // Initialize segment tree
  memset(c + M, 192, sizeof c / 2);
  dfs(1, 0, 0);
  // Propagate values up the segment tree
  per(i, M - 1, 1) c[i][0] = max(c[i * 2][0], c[i * 2 + 1][0]), pu(i);
  cin >> m;
  while (m--) {
    cin >> u >> v, u = dfn[u] + M;
    // Update the node with new weight
    c[u][1] = v, c[u][2] = dep[u - M] + v, c[u][4] = v - dep[u - M];
    // Propagate changes up the tree
    while (u >>= 1)
      pu(u);
    // Calculate and output the radius
    cout << max(c[1][1], c[1][5] + 3 >> 1) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/