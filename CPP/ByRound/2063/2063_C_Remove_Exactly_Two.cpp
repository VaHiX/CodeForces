// Problem: CF 2063 C - Remove Exactly Two
// https://codeforces.com/contest/2063/problem/C

/*
C. Remove Exactly Two
Time Complexity: O(n) per test case
Space Complexity: O(n)

Algorithms/Techniques: Tree DFS, Dynamic Programming on Tree

This solution computes the maximum number of connected components that can be obtained
by removing exactly two vertices from a tree. The key idea is to use depth-first search
to process each node and compute for each node the maximum number of connected
components that can be formed by deleting one or two nodes, using dynamic programming
on the tree structure.

The algorithm maintains:
- f[x]: maximum number of components obtainable starting from node x when one vertex is deleted.
- For each node, we try all combinations of removing two vertices (one from current and one from child)
  to compute the maximum possible connected components.
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int T, n, f[200005], ans; // f[x] stores max number of components for subtree rooted at x using one removal
vector<int> q[200005]; // adjacency list representation of the tree

void dfs(int x, int fa) {
  int r = q[x].size(); // degree of current node x
  for (int i = 0; i < q[x].size(); i++) {
    int v = q[x][i];
    if (v == fa)
      continue;
    dfs(v, x); // recursively process child v
    
    // Update answer with combinations of removing nodes
    ans = max(ans, r + (int)q[v].size() - 2); 
    ans = max(ans, r + f[v] - 1);
    ans = max(ans, f[x] + max(f[v], (int)q[v].size()) - 1);
    
    // Update f[x] with the best value from this child
    f[x] = max(f[x], max(f[v], (int)q[v].size()));
  }
}

void solve() {
  scanf("%d", &n);
  ans = 0;
  for (int i = 1; i <= n; i++)
    f[i] = 0, q[i].clear();
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    q[u].push_back(v);
    q[v].push_back(u);
  }
  dfs(1, 0); // start DFS from root 1
  printf("%d\n", ans);
}

signed main() {
  scanf("%d", &T);
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/