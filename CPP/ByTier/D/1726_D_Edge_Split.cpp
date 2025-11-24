// Problem: CF 1726 D - Edge Split
// https://codeforces.com/contest/1726/problem/D

/*
Algorithm: 
This code finds an optimal assignment of edges to red (1) or blue (0) in a connected undirected graph to minimize the sum of connected components in the subgraphs formed by red and blue edges. It uses Union-Find (Disjoint Set Union) data structure to detect cycles and determine which edges are essential for connectivity.

Key Insight:
- If an edge is part of a cycle, coloring it red will not increase the number of connected components in the red subgraph.
- The goal is to isolate as many cycles as possible, and assign one edge from each cycle to red (which reduces component count in red subgraph), while keeping the rest blue.
- If total edges are n + 2, there could be up to 2 extra edges beyond a spanning tree, and possibly up to 2 cycles or a triangle involving 3 nodes. If there is a structure like that, it needs special handling to assign the edge appropriately.

Time Complexity: O(m * α(n)) where α(n) is the inverse Ackermann function, nearly constant.
Space Complexity: O(n + m) for storing graph data and Union-Find arrays.
*/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
enum { N = 200009 };
int x[N], y[N], f[N]; // x,y stores edges, f is for Union-Find
bool b[N]; // b[i] indicates if edge i is red (1) or blue (0)
int gf(int x) { return f[x] == x ? x : f[x] = gf(f[x]); } // Find with path compression
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T, n, m, i, j, k, w;
  vector<int> v; // Stores nodes involved in cycles
  for (cin >> T; T--;) {
    cin >> n >> m;
    w = 0; // Index of a key edge
    v = {}; // Reset vector
    for (i = 1; i <= n; ++i)
      f[i] = i; // Initialize Union-Find
    for (i = 1; i <= m; ++i) {
      cin >> x[i] >> y[i];
      b[i] = 0; // Initially all edges are blue
      if (gf(x[i]) == gf(y[i])) { // If adding this edge creates a cycle
        b[i] = 1; // Mark it red
        w = i; // Record index of a cycle edge
        v.push_back(x[i]), v.push_back(y[i]); // Add nodes to cycle
      } else
        f[gf(x[i])] = gf(y[i]); // Union the two components
    }
    sort(begin(v), end(v));
    v.resize(unique(begin(v), end(v)) - begin(v)); // Remove duplicates from cycle nodes
    if (m - n == 2 && v.size() == 3) { // Special case for exactly 2 extra edges forming a triangle
      for (i = 1; i <= n; ++i)
        f[i] = i; // Reinitialize Union-Find
      f[gf(x[w])] = gf(y[w]); // Marking the cycle edge to connect components
      for (i = 1; i <= m; ++i)
        if (!b[i]) { // For non-cycle edges
          if (gf(x[i]) == gf(y[i]))
            b[i] = 1; // If connecting to existing component, color red
          else
            f[gf(x[i])] = gf(y[i]); // Union
        }
      b[w] = 0; // Revert the cycle edge back to blue in special case
    }
    for (i = 1; i <= m; ++i)
      cout << b[i]; // Output edge colorings
    cout << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/