// Problem: CF 1610 H - Squid Game
// https://codeforces.com/contest/1610/problem/H

/*
 * Problem: Squid Game
 * Algorithm: Tree DP with Binary Lifting + Greedy
 * 
 * Time Complexity: O(n log n + m)
 * Space Complexity: O(n + m)
 * 
 * Approach:
 * 1. Build tree using parent relationships.
 * 2. Use binary lifting to compute ancestors and depths.
 * 3. For each player, determine if their path can be covered by choosing a vertex.
 * 4. Classify players into two types:
 *    - Type 1: Player whose path starts at node w and ends at node u, with w being the lowest common ancestor.
 *    - Type 2: Player whose path has no vertex at lca except endpoints.
 * 5. Use tree DP to compute minimum operations needed.
 * 6. Finally, compute answer by considering all type 2 players.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define N 300005
int n, m;
std::vector<int> E[N];
#define W 20
int fa[N][W], dep[N];
inline void dfs(int u) {
  // Precompute ancestors for binary lifting
  for (int i = 1; i < W; i++)
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  dep[u] = dep[fa[u][0]] + 1;
  for (auto v : E[u])
    dfs(v);
}
inline int jmp(int u, int v) {
  // Jump u up to the same depth as v, then find LCA
  for (int i = W - 1; ~i; i--)
    if (dep[fa[u][i]] > dep[v])
      u = fa[u][i];
  return u;
}
std::vector<int> A[N];  // Stores children for type 1 players (to be processed by DP)
std::vector<std::pair<int, int>> B;  // Stores type 2 players (no shared vertex at LCA)
int f[N];  // DP states for subtree
inline void dp(int u) {
  // Compute DP values for subtree rooted at u
  for (auto v : E[u])
    dp(v), f[u] += f[v];
  // Update f[u] based on type 1 players
  for (auto v : A[u])
    f[u] = std::max(f[u], f[v] + 1);
}
int ans;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i][0]);
    E[fa[i][0]].push_back(i);
  }
  dfs(1);  // Build binary lifting table and depth
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (dep[u] < dep[v])
      std::swap(u, v);  // Make sure u is deeper
    int w = jmp(u, v);  // Find LCA
    if (fa[w][0] == v) {
      // If v is the parent of LCA, then the path is from w to u
      if (w == u)
        return puts("-1"), 0;  // Invalid case
      A[w].push_back(u);  // Add to type 1 group
    } else
      B.emplace_back(u, v);  // Add to type 2 group
  }
  dp(1);  // Compute dp values
  ans = f[1];
  for (auto [u, v] : B)
    // Consider type 2 players: we need to eliminate both ends, so combine dp values
    ans = std::max(ans, f[u] + f[v] + 1);
  printf("%d\n", ans);
}


// https://github.com/VaHiX/CodeForces/