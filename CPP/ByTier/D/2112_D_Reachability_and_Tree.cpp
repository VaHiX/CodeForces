// Problem: CF 2112 D - Reachability and Tree
// https://codeforces.com/contest/2112/problem/D

/*
D. Reachability and Tree
time limit per test2 seconds
memory limit per test256 megabytes

Task:
Given an undirected tree with n vertices, determine whether it is possible to assign a direction to each edge so that exactly n pairs (u,v) exist such that there is a directed path from u to v.
If possible, output any valid orientation of edges.

Algorithms/Techniques:
- Graph traversal (DFS)
- Tree properties and edge orientation logic
- Identifying special structure in tree for valid assignment

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The approach is based on the idea that for a tree to have exactly n good pairs,
we must orient edges such that only vertices with degree 2 can be part of a cycle-like structure
that allows for exactly n directed pairs. A key insight is that if there exists a vertex of degree 2,
we can use a DFS-like traversal strategy where we direct edges along specific paths to achieve n good pairs.

For each test case:
- If there's a node with degree 2, construct the solution by traversing from neighbors of this node
- The solution involves directing edges away from the central vertex of degree 2,
  forming a tree-like structure that allows for exactly n good pairs.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
vector<vector<int>> gr;

// Function f(x, p, c): recursive DFS to orient edges
// x: current node, p: parent node, c: flag indicating direction of edge (0 or 1)
void f(int x, int p, int c) {
  for (auto y : gr[x]) {             // Iterate through neighbors of current node
    if (c)                           // If edge should be directed from x to y
      cout << x + 1 << ' ' << y + 1 << '\n';
    if (y != p)                      // Avoid going back to parent
      f(y, x, c ^ 1);                // Recurse with flipped direction flag
  }
}

void solve() {
  int n;
  cin >> n;
  gr.clear();
  gr.resize(n);
  for (int i = 0; i < n - 1; ++i) {  // Read the tree edges and build adjacency list
    int u, v;
    cin >> u >> v;
    u--, v--;
    gr[u].push_back(v);
    gr[v].push_back(u);
  }
  
  for (int i = 0; i < n; ++i) {      // Find a node with degree 2
    if (gr[i].size() == 2) {
      cout << "YES\n";
      f(gr[i][0], i, 1);           // Start traversing from one neighbor
      f(gr[i][1], i, 0);           // Continue from another neighbor
      cout << i + 1 << ' ' << gr[i][1] + 1 << '\n'; // Final edge direction
      return;
    }
  }
  
  cout << "NO\n";                    // No valid orientation found
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/