// Problem: CF 1788 F - XOR, Tree, and Queries
// https://codeforces.com/contest/1788/problem/F

/*
Algorithm: 
This problem involves assigning weights to edges in a tree such that certain XOR conditions on paths are satisfied.
It uses a combination of graph traversal (DFS), XOR properties, and connected components to determine if a valid assignment exists.
We treat each condition as a constraint between two nodes. For a set of paths, we compute XOR of all edge weights on the path 
between two nodes and match it with the given value.

The approach:
1. Build adjacency list representation of the tree.
2. For every query condition (u, v, x), store the constraint in two directions (u -> v and v -> u).
3. Perform DFS to detect inconsistencies:
   - Propagate XOR values from root in tree traversal.
   - Detect contradictions in XOR calculations.
4. If no contradiction, solve for the minimum XOR of all edges by solving a system of linear equations over GF(2).

Time Complexity: O(N + Q), where N is the number of nodes and Q is the number of queries.
Space Complexity: O(N + Q), for storing the graph and auxiliary data structures.

*/
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int N = 300010;
bool vis[N], bad; // vis tracks visited nodes, bad marks inconsistency
vector<int> comp; // stores nodes in current component
vector<pair<int, int>> g[N]; // adjacency list with edge weights stored as part of edges
int n, q, U[N], V[N], deg[N], sum[N], goodXor, goodCount; // sum: XOR values from root, goodXor/Count: for connected components
void go(int u) {
  vis[u] = 1, comp.emplace_back(u); // Mark node as visited, add to component
  if (deg[u] & 1) // If degree is odd, update parity of the component
    goodCount ^= 1, goodXor ^= sum[u];
  for (auto [v, w] : g[u]) { // Traverse neighbors
    if (vis[v]) { // Back edge (cycle detection)
      if (sum[u] ^ sum[v] ^ w) // XOR constraint check
        bad = true; // Inconsistency found
    } else {
      sum[v] = sum[u] ^ w, go(v); // Propagate XOR sum to neighbor
    }
  }
}
int main() {
  cin >> n >> q;
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", U + i, V + i);
    ++deg[U[i]], ++deg[V[i]]; // Count degrees for odd-degree nodes
  }
  while (q--) {
    int u, v, x;
    scanf("%d %d %d", &u, &v, &x);
    g[u].emplace_back(v, x); // Store constraint in both directions
    g[v].emplace_back(u, x);
  }
  int ansXor = 0; // XOR of the entire solution
  vector<int> certainComp; // Component with odd degree nodes to determine global offset
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) {
      goodXor = goodCount = 0, comp.clear(), go(i), ansXor ^= goodXor; // Process each component
      if (goodCount and certainComp.empty()) // If component has odd degree, save it
        certainComp = comp;
    }
  if (bad) {
    cout << "No\n";
    return 0;
  }
  for (int u : certainComp) // Adjust sum of each node in component by XOR of global solution
    sum[u] ^= ansXor;
  cout << "Yes\n";
  for (int i = 1; i < n; ++i) // Output edge weights by XORing both ends of each edge
    cout << (sum[U[i]] ^ sum[V[i]]) << " ";
  cout << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/