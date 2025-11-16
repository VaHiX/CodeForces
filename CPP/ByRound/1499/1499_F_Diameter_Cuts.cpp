// Problem: CF 1499 F - Diameter Cuts
// https://codeforces.com/contest/1499/problem/F

/*
 * Problem: Diameter Cuts
 * 
 * Purpose: Count the number of valid sets of edges to remove from a tree such that
 *          all resulting connected components have diameter at most k.
 * 
 * Algorithm:
 * - Use dynamic programming on trees with subtree DP.
 * - For each node u, maintain a DP table f[u][i] representing the number of ways
 *   to cut edges in the subtree of u such that the resulting tree rooted at u has
 *   diameter exactly i.
 * - When merging subtrees, compute new values for f[u][i] based on combinations
 *   from the current node and its children to ensure that all resulting trees
 *   satisfy the diameter constraint.
 * 
 * Time Complexity: O(n * k^2)
 * Space Complexity: O(n * k)
 * 
 * Approach:
 * - DFS traversal of the tree from root node (node 1).
 * - For each node u and each child v, combine the DP values from u and v.
 * - The key idea is to keep track of how many combinations result in a valid diameter.
 * - At the end, sum over all valid diameters from root to get the answer.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define N 5050
const int p = 998244353;
vector<int> e[N];
int f[N][N], n, m, d[N], k, g[N];

void dfs(int u, int fa) {
  d[u] = 0; // Initialize the maximum diameter of subtree rooted at u
  f[u][0] = 1; // Base case: 1 way to have diameter 0 (empty set of edges cut)
  for (auto v : e[u]) // For each child v in the tree
    if (v != fa) { // Avoid going back to parent
      dfs(v, u); // Recursively process the subtree rooted at v
      // Temporary array g[i] accumulates DP transitions
      for (int i = 0; i <= d[u] && i <= k; ++i)
        for (int j = 0; j <= d[v] && j <= k; ++j) {
          // Combine the number of valid cuts of subtree u and subtree v
          // Add the number of ways that both trees remain (diameter i+j+1 <= k)
          (g[i] += 1ll * f[u][i] * f[v][j] % p) %= p;
          // Add the cases where one subtree is extended (diameter max(i, j+1))
          if (i + j + 1 <= k)
            (g[max(i, j + 1)] += 1ll * f[u][i] * f[v][j] % p) %= p;
        }
      d[u] = max(d[u], d[v] + 1); // Update diameter of current subtree
      // Copy accumulated results to f[u]
      for (int i = 0; i <= d[u] && i <= k; ++i)
        f[u][i] = g[i], g[i] = 0;
    }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> k;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1, 0); // Start DFS from root node 1
  int res = 0;
  for (int i = 0; i <= k; ++i)
    (res += f[1][i]) %= p; // Sum all valid combinations for the full tree
  cout << res << "\n";
}


// https://github.com/VaHiX/CodeForces/