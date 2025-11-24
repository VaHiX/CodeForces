// Problem: CF 1681 F - Unique Occurrences
// https://codeforces.com/contest/1681/problem/F

/*
 * Problem: F. Unique Occurrences
 * 
 * Algorithm: Tree Dynamic Programming with Edge Value Frequency Tracking
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Approach:
 * - For each unique edge value, we track which nodes are affected by this value on paths.
 * - We use DFS traversal of the tree to compute for each edge the number of nodes 
 *   that, through the path from root, are connected to a subtree where the value appears.
 * - The contribution of each edge value to the final result is computed based on 
 *   how many pairs of nodes (u, v) have exactly one occurrence of that value on their path.
 * 
 * Key idea:
 * - For every edge with value w, we maintain a stack A[w] storing the nodes involved.
 * - During DFS, we track the "father" of each node (ff[v]) to adjust contributions.
 * - We compute g[v] as the number of times node v contributes to counting unique values.
 * - Final answer is computed by summing over all nodes: g[v] * g[ff[v]].
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define N 1000100
typedef long long ll;
int n, g[N], siz[N], ff[N];
vector<pair<int, int>> G[N];
vector<int> A[N];
ll ans;

// DFS traversal to compute contribution of each edge value
void dfs(int u, int fa) {
  siz[u] = 1;
  for (auto [v, w] : G[u]) {
    if (v == fa)
      continue;
    ff[v] = A[w].back(); // Store parent of current node for this value
    A[w].push_back(v);   // Add current node to stack for value w
    dfs(v, u);           // Recurse
    siz[u] += siz[v];    // Update subtree size
    g[v] += siz[v];      // Increment contribution of node v
    g[ff[v]] -= siz[v];  // Decrement contribution of parent node of v
    A[w].pop_back();     // Backtrack: remove from stack
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  
  // Read edges
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  
  // Initialize A[] and g[] arrays
  for (int i = 1; i <= n; ++i) {
    A[i].push_back(n + i); // Initialize with dummy value
    g[n + i] = n;          // Initialize g with large value
  }
  
  dfs(1, 0); // Start DFS from node 1

  // Compute final result by summing up contributions
  for (int i = 2; i <= n; ++i) {
    ans += 1LL * g[i] * g[ff[i]];
  }
  
  cout << ans << '\n';
  return 0;
}


// https://github.com/VaHiX/CodeForces/