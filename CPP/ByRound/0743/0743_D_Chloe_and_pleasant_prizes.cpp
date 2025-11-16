// Problem: CF 743 D - Chloe and pleasant prizes
// https://codeforces.com/contest/743/problem/D

/*
Purpose: Solve the problem of selecting two non-intersecting subtrees from a tree such that the sum of pleasantness values is maximized.
Algorithm: 
- Build an undirected tree from input edges.
- Use DFS to compute for each node:
  - f[x]: total sum of pleasantness in subtree rooted at x.
  - dp[x]: maximum sum of pleasantness in any subtree rooted at x that does not include the parent path.
- During DFS traversal, for each node, we check:
  - Update global answer with max of dp[x] + dp[u] for children u.
  - Maintain dp[x] as the maximum among all dp[u] values for children u, or f[x] if no better choice.
Time Complexity: O(n)
Space Complexity: O(n)
*/
#include <algorithm>
#include <cstdio>
typedef long long ll;
const int N = 200010;
const ll inf = 1LL << 60;
int n, i, x, y, a[N], g[N], v[N << 1], nxt[N << 1], ed;
ll f[N], dp[N], ans = -inf;

// Add an edge to the adjacency list representation of the graph
inline void add(int x, int y) {
  v[++ed] = y;
  nxt[ed] = g[x];
  g[x] = ed;
}

// DFS traversal to calculate f and dp for each node
void dfs(int x, int y) {
  f[x] = a[x]; // Initialize f[x] with the value of current node
  dp[x] = -inf; // Initialize dp[x] as negative infinity
  for (int i = g[x]; i; i = nxt[i]) { // Iterate through neighbors
    int u = v[i];
    if (u == y) // Skip the parent
      continue;
    dfs(u, x); // Recursively process child
    f[x] += f[u]; // Accumulate sum of subtree
    if (dp[x] > -inf) // If dp[x] has been updated, check combination
      ans = std::max(ans, dp[x] + dp[u]);
    dp[x] = std::max(dp[x], dp[u]); // Update dp[x] with max of children dp values
  }
  dp[x] = std::max(dp[x], f[x]); // Choose the better of dp[x] or total subtree sum
}

int main() {
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (i = 1; i < n; i++)
    scanf("%d%d", &x, &y), add(x, y), add(y, x); // Build bidirectional graph
  dfs(1, 0); // Start DFS from root (node 1)
  if (ans > -inf)
    printf("%I64d", ans);
  else
    puts("Impossible");
}


// https://github.com/VaHiX/CodeForces/