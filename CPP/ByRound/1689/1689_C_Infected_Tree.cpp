// Problem: CF 1689 C - Infected Tree
// https://codeforces.com/contest/1689/problem/C

/*
Purpose: 
  This code solves the problem of maximizing the number of vertices saved from infection in a binary tree,
  where the infection starts at the root (vertex 1). At each step, we can choose to delete a non-infected vertex
  (and all edges connected to it), which stops the infection from spreading further through that part of the tree.
  The goal is to find the maximum number of vertices that can be saved.

Algorithms/Techniques:
  - Tree Dynamic Programming (DP)
  - DFS traversal to compute subtree sizes and optimal deletion strategy
  - For each node, we calculate the best decision about whether to delete a child subtree to maximize vertices saved

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the tree and auxiliary arrays

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<long long> e[300005];  // Adjacency list representation of the tree
long long T, n, m, u, v, sz[300005], dp[300005], t;

// DFS function to calculate subtree sizes and optimal saved vertices
void dfs(long long x, long long fa) {
  sz[x] = 1;  // Initialize size of current subtree
  for (auto xx : e[x]) {
    if (xx == fa)
      continue;  // Skip parent to avoid going back up the tree
    dfs(xx, x);  // Recursively process child
    sz[x] += sz[xx];  // Add child subtree size to current subtree size
    dp[x] += dp[xx];  // Add child's optimal saved vertices to current
  }
  t = dp[x];  // Store current dp value before modifying it
  for (auto xx : e[x])
    if (xx != fa)
      // Decide whether to delete this child subtree:
      // either keep current dp[x], or delete this child subtree and save sz[xx] - 1 more vertices
      dp[x] = max(dp[x], t - dp[xx] + sz[xx] - 1);
}

int main() {
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 0; i <= n; i++)
      dp[i] = 0;  // Reset dp array
    for (int i = 0; i <= n; i++)
      e[i].clear();  // Clear adjacency list
    for (int i = 1; i < n; i++) {
      cin >> u >> v;
      e[u].push_back(v);  // Add edge u-v
      e[v].push_back(u);  // Add edge v-u
    }
    dfs(1, 0);  // Start DFS from root (vertex 1)
    cout << dp[1] << endl;  // Output maximum saved vertices starting from root
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/