// Problem: CF 734 E - Anton and Tree
// https://codeforces.com/contest/734/problem/E

/*
 * Problem: Anton and Tree
 * Algorithm: Tree Diameter + DFS
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * The approach is to find the diameter of the tree by performing two DFS traversals:
 * 1. Start DFS from any node (node 1) to find the farthest node.
 * 2. Start DFS from that farthest node to find the actual diameter.
 * 
 * The minimum number of operations needed is (1 + diameter) / 2.
 * This is because each operation can "paint" all nodes in a path from a vertex,
 * and the diameter gives us the longest path in the tree.
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
vector<vector<int>> G;       // adjacency list representation of the tree
vector<int> color;           // color of each vertex (0 = white, 1 = black)
pair<int, int> rec;          // used to store {depth, vertex} during DFS
int n;

// DFS traversal to find the farthest node from the starting vertex
// 'v' is current vertex, 'p' is parent, 'depth' is current depth
void dfs(int v, int p, int depth) {
  rec = max(rec, {depth, v});  // update the maximum depth and corresponding vertex
  for (auto to : G[v]) {       // iterate over neighbors
    if (to == p)               // skip the parent to avoid backtracking
      continue;
    if (color[to] == color[v]) // if neighbor has same color, depth doesn't increase
      dfs(to, v, depth);
    else                       // else depth increases by 1
      dfs(to, v, depth + 1);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  G.resize(n + 1);      // resize adjacency list
  color.resize(n + 1);  // resize color array

  // Read colors of nodes
  for (int i = 1; i <= n; ++i)
    cin >> color[i];

  // Read edges and build the adjacency list
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  // First DFS: start from node 1 to find one end of the diameter
  dfs(1, 0, 0);
  rec.first = -1;  // reset for second DFS

  // Second DFS: start from the node found in first DFS to find the actual diameter
  dfs(rec.second, 0, 0);

  // The minimum number of operations is (1 + diameter) / 2
  cout << (1 + rec.first) / 2 << endl;
}


// https://github.com/VaHiX/CodeForces/