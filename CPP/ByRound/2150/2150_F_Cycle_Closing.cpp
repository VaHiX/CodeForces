// Problem: CF 2150 F - Cycle Closing
// https://codeforces.com/contest/2150/problem/F

/*
F. Cycle Closing

This code solves the problem of making an undirected, connected graph complete in at most 2 operations.
Each operation involves choosing a path length k and printing s simple paths of that length,
and then adding shortcut edges (first vertex to last vertex of each path) to the graph.

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) for tracking connected components
- BFS/DFS for computing distances between nodes in the graph
- Path finding and edge insertion logic based on distance properties

Time Complexity: O(n^3) per test case due to nested loops for path construction and distance computations.
Space Complexity: O(n^2) for storing adjacency information, distances, parent pointers, and neighbor lists.

*/

#include <algorithm>
#include <bitset>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
constexpr int N = 200;
int pp[N], d[N][N], p[N][N];          // pp: Union-Find parent, d: distance matrix, p: parent matrix
bitset<N> adj[N];                     // adj: adjacency bitset for quick edge checks
vector<int> nei[N];                   // nei: neighbor list for tree construction

// Find root of component with path compression
int getp(int v) { return pp[v] == v ? v : pp[v] = getp(pp[v]); }

// Union two components, returns true if they were separate
bool uni(int a, int b) {
  return getp(a) == getp(b) ? 0 : (pp[pp[a]] = pp[b], 1);
}

// DFS to compute distances from root r and set parent relationships
void calcd(int r, int v, int cd) {
  d[r][v] = cd;
  for (auto u : nei[v])
    if (!~d[r][u])
      p[r][u] = v, calcd(r, u, cd + 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (int tc = (cin >> tc, tc); tc--;) {
    int n, m;
    cin >> n >> m;
    // Initialize data structures
    for (int i = 0; i < n; ++i)
      pp[i] = i, adj[i].reset(), nei[i] = {};
    
    // Process edges: build the spanning tree using Union-Find
    for (int a, b; m--;)
      if (cin >> a >> b, --a, --b, adj[a][b] = adj[b][a] = 1, uni(a, b))
        nei[a].push_back(b), nei[b].push_back(a);
    
    // Initialize distance matrix with -1
    fill(d[0], d[n], -1);
    
    // Compute all-pairs distances using BFS from each node
    for (int i = 0; i < n; ++i)
      p[i][i] = -1, calcd(i, i, 0);
    
    vector<vector<int>> pths;  // Store edge shortcuts found
    
    // Find triangles and record shortcut edges
    for (int i = 0; i < n; ++i)
      for (auto j : nei[i])
        for (auto k : nei[j])
          if (k < i && !adj[i][k])
            pths.push_back({i + 1, j + 1, k + 1}), adj[i][k] = adj[k][i] = 1;
    
    // Output first operation's results (k=3, #paths = number of triangles found)
    cout << "2 3 " << pths.size() << ' ';
    for (auto &v : pths)
      for (auto &v : v)
        cout << v << ' ';
    pths = {};  // Reset vector for use in second operation
    
    // Determine the middle distance of a longest path to guide further processing
    int l = ({
      int a = max_element(d[0], d[1]) - d[0];   // Find node farthest from first node
      *max_element(d[a], d[a + 1]) + 1 >> 1;     // Compute middle of diameter
    });
    
    cout << l + 1 << ' ';  // Output k for second operation
    
    // Find all possible paths to add edges to make complete graph
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
        if (!adj[i][j])   // For missing edges
          if (d[i][j] >= l) {
            int v = j, w = 0;
            vector<int> pth{v};
            while (v != i)
              pth.push_back(v = p[i][v]);  // Trace path from i to j
            
            // Simplify path - only keep every other vertex
            for (int i = 0; i < pth.size(); ++i)
              if (i % 2 == 0 || pth.size() - i + w == l + 1)
                pth[w++] = pth[i] + 1;
            pth.resize(w);
            pths.push_back(move(pth));
          } else {
            int v = -1;
            // Find a node on the path
            for (int k = 0; !~v; ++k)
              if (d[i][k] + d[j][k] == 2 * l - d[i][j])
                v = k;
            
            vector<int> pth[2];  // Two subpaths
            
            // Build path from i to v
            for (int t = 0; pth[t].push_back(v + 1), p[i][v] == p[j][v]; t ^= 1)
              v = p[i][v];
            
            // Adjust direction based on last node
            if (pth[1].size() && pth[1].back() == i + 1 ||
                pth[0].back() == j + 1)
              swap(pth[1], pth[0]);
            
            // Add rest of path from v to i and j
            for (int u = v; u != i; u = p[i][u], pth[0].push_back(u + 1))  ;
            for (int u = v; u != j; u = p[j][u], pth[1].push_back(u + 1))  ;
            
            // Merge paths
            pth[0].insert(pth[0].begin(), pth[1].rbegin(), pth[1].rend());
            pths.push_back(move(pth[0]));
          }
    
    cout << pths.size() << ' ';  // Output number of paths in second operation
    
    // Print all paths
    for (auto &v : pths)
      for (auto &v : v)
        cout << v << ' ';
  }
}


// https://github.com/VaHiX/CodeForces/