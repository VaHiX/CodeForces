// Problem: CF 2114 E - Kirei Attacks the Estate
// https://codeforces.com/contest/2114/problem/E

/*
E. Kirei Attacks the Estate
Algorithms/Techniques: Tree DFS, Dynamic Programming on Trees

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem requires computing for each vertex in a tree the maximum alternating sum along paths from that vertex to the root.
We use a depth-first search (DFS) starting from the root node 1. For each node, we maintain two values:
- mx[v]: the maximum alternating sum ending at node v
- mn[v]: the minimum alternating sum ending at node v

These values are updated during DFS traversal based on parent's values and current node's value.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
long long a[N], mn[N], mx[N]; // Arrays to store node values, min alternating sum, max alternating sum
vector<int> e[N];             // Adjacency list for the tree

void dfs(int u, int fa) {
  // Iterate through all neighbors of node u
  for (size_t i = 0; i < e[u].size(); i++) {
    int v = e[u][i];
    if (v == fa)            // Skip parent to avoid cycles
      continue;
    
    // Update max and min alternating sum for child node v based on parent node u
    mx[v] = max(a[v], a[v] - mn[u]);   // Compute maximum alternating sum ending at v
    mn[v] = min(a[v], a[v] - mx[u]);   // Compute minimum alternating sum ending at v
    
    dfs(v, u);  // Recursively process child node
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i], e[i].clear();  // Read node values and clear adjacency list
    
    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      e[u].push_back(v), e[v].push_back(u);  // Build adjacency list
    }
    
    mx[1] = mn[1] = a[1];  // Initialize root node values
    
    dfs(1, 0);  // Begin DFS from root
    
    for (int i = 1; i <= n; i++)
      cout << mx[i] << " ";  // Output the maximum alternating sum for each node
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/