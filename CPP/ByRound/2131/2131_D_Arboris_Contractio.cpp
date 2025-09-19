// Problem: CF 2131 D - Arboris Contractio
// https://codeforces.com/contest/2131/problem/D

/*
D. Arboris Contractio
Purpose: Given a tree, find the minimum number of operations to minimize its diameter.
Each operation allows choosing two vertices s and t, removing the path between them,
and connecting all vertices on that path directly to s.

Algorithms/Techniques:
- Tree traversal and degree calculation
- Identify leaf nodes and their parents
- Count how many leaves are attached to each node (to determine the maximum number of leaves
  that can be "merged" into one node using a single operation)
- The result is total leaves minus the maximum number of leaves under a single parent.

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing degree, parent, and leaf count arrays.

*/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_NODES = 2e5 + 5;

void solve() {
  int n;
  cin >> n;
  vector<int> degree(n + 1, 0);       // Store the degree of each node
  vector<int> parent(n + 1, 0);       // Store the parent of each node
  vector<int> leaf_count(n + 1, 0);   // Count how many leaves are under each node
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    degree[u]++;     // Increment the degree of u and v
    degree[v]++;
    parent[u] = v;   // Record parent relationships
    parent[v] = u;
  }

  if (n == 2) {        // Special case: a tree with only two nodes has diameter 1
    cout << "0\n";
    return;
  }

  int total_leaves = 0;     // Total number of leaves in the tree
  int max_leaves = 0;       // Maximum number of leaves connected to any single node

  for (int i = 1; i <= n; i++) {
    if (degree[i] == 1) {   // If node is a leaf (degree 1)
      total_leaves++;
      int parent_node = parent[i];   // Get the parent of this leaf
      leaf_count[parent_node]++;     // Count how many leaves are under this parent
      max_leaves = max(max_leaves, leaf_count[parent_node]);   // Track maximum
    }
  }

  cout << total_leaves - max_leaves << '\n';   // Minimum operations needed
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int test_cases;
  cin >> test_cases;
  while (test_cases--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/