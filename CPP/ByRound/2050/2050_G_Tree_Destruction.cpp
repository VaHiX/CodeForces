// Problem: CF 2050 G - Tree Destruction
// https://codeforces.com/contest/2050/problem/G

/*
G. Tree Destruction
Algorithms/Techniques: Dynamic Programming on Trees, DFS traversal
Time Complexity: O(n) per test case
Space Complexity: O(n) for adjacency list and auxiliary arrays

Given a tree with n vertices, we can remove all vertices on the path from 
two chosen vertices a and b (including a and b). The goal is to maximize 
the number of connected components after the removal.

This solution uses DFS to compute the maximum number of components by 
considering each node as a potential "center" of a path that splits the tree,
trying to remove edges such that the maximum number of disconnected parts occurs.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
int T, n, u, v, d[maxn], ans;
vector<int> e[maxn];

// DFS function to compute the maximum number of components
// Returns the maximum depth from current node considering removals
int dfs(int u, int fa) {
  int mx = d[u]; // Initialize max depth with degree of current node
  ans = max(ans, mx); // Update global answer

  for (int &v : e[u]) // Iterate through neighbors
    if (v != fa) { // Skip parent to avoid going back
      int x = dfs(v, u); // Recursively process child subtree
      ans = max(ans, mx + x - 2); // Update answer with possible split
      mx = max(mx, d[u] + x - 2); // Update max depth including current path
    }
  e[u].clear(); // Clear adjacency list to save memory (avoid reuse)
  return mx;
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ans = 0;
    for (int i = 1; i < n; i++) {
      scanf("%d%d", &u, &v);
      e[u].emplace_back(v); // Build adjacency list
      e[v].emplace_back(u);
      d[u]++; // Increment degree
      d[v]++;
    }
    dfs(1, 0); // Start DFS from root node (1) with no parent (0)
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
      d[i] = 0; // Reset degrees for next test case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/