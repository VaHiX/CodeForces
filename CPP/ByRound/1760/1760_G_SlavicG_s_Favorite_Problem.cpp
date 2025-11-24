// Problem: CF 1760 G - SlavicG's Favorite Problem
// https://codeforces.com/contest/1760/problem/G

/*
G. SlavicG's Favorite Problem
Algorithms/Techniques: DFS traversal on tree, XOR properties, teleportation optimization
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

This problem involves finding a path in a weighted tree from node 'a' to node 'b'
such that the XOR value of all edges traversed becomes 0 upon reaching 'b'.
Additionally, one teleportation is allowed at any point in the journey.

The solution uses two DFS traversals:
1. dfs1: From node S, collect all possible XOR values that can be achieved while traversing
   the tree (excluding T). These are stored in a set for quick lookup.
2. dfs2: From node T, perform DFS to find if there exists any path such that
   XOR value from root to current node XOR edge weight equals some value already collected.

The key idea is based on XOR properties:
If x ^ w = 0, then x = w.
When we can teleport to a node u and continue, the problem reduces to
checking whether starting from S we can find a path whose XOR sum of edges
plus some value (from teleported position) gives a value that exists in our set.

*/

#include <stdio.h>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
int S, T;
map<int, vector<pair<int, int>>> to;  // adjacency list with edge weights
set<int> g;                         // stores XOR values from S to nodes (excluding T)

void dfs1(int u, int f, int x) {
  g.insert(x);  // insert current XOR value into set
  for (auto [w, wt] : to[u]) {
    if (w != f && w != T)  // avoid parent and target node
      dfs1(w, u, x ^ wt);  // continue DFS with updated XOR value
  }
}

int dfs2(int u, int f, int x) {
  int suc = 0;
  for (auto [w, wt] : to[u]) {
    if (w == f)
      continue;  // skip parent node
    
    if (g.count(x ^ wt))  // check if complement exists in set
      return 1;
    
    int aabb;
    suc |= dfs2(w, u, x ^ wt);  // recurse further
  }
  return suc;
}

int main() {
  int t, u, v, w, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &n, &S, &T);
    g.clear();
    to.clear();
    for (int i = 1; i < n; i++) {
      scanf("%d%d%d", &u, &v, &w);
      to[u].push_back({v, w});
      to[v].push_back({u, w});
    }
    dfs1(S, 0, 0);          // populate set g with XOR values from S
    puts(dfs2(T, 0, 0) ? "YES" : "NO");  // check if path exists ending in T with XOR = 0
  }
}


// https://github.com/VaHiX/codeForces/