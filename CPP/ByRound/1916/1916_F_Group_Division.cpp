// Problem: CF 1916 F - Group Division
// https://codeforces.com/contest/1916/problem/F

/*
 * Problem: F. Group Division
 * 
 * Purpose:
 *   This code solves the problem of dividing a set of people into two groups (Computer Science and Mathematics),
 *   such that all members within each group are mutually acquainted (directly or through mutual friends).
 *   It uses a graph-based approach with Tarjan's algorithm to identify connected components and then performs
 *   a DFS to assign groups.
 *   
 * Algorithm:
 *   - Build an undirected graph from the input edges.
 *   - Use Tarjan's algorithm (Strongly Connected Components) to identify biconnected components.
 *   - Perform DFS in the resulting component graph to assign nodes to groups based on the connected structure.
 *   - Output the assignments for the two groups.
 *   
 * Time Complexity: O(n + m), where n = n1 + n2 is the number of nodes, and m is the number of edges.
 * Space Complexity: O(n + m), for storing the adjacency list and auxiliary arrays.
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
int T, n1, n2, m, n, a, b, e[10005], ne[10005], h[4005], idx, dfn[4005],
    low[4005], dcnt, rk[4005], ans[4005], cnt, vis[4005];
vector<int> v[4005];

// Add an edge to the adjacency list representation of the graph
inline void add(int a, int b) { e[idx] = b, ne[idx] = h[a], h[a] = idx++; }

// Tarjan's algorithm to find biconnected components and build the block-cut tree
void tar(int u, int fa) {
  dfn[u] = low[u] = ++dcnt, rk[dcnt] = u;
  for (int i = h[u]; i; i = ne[i]) {
    if (!dfn[e[i]])
      tar(e[i], u), low[u] = min(low[u], low[e[i]]), v[u].push_back(e[i]),
                    v[rk[low[e[i]]]].push_back(e[i]);
    else if (e[i] != fa)
      low[u] = min(low[u], dfn[e[i]]);
  }
}

// DFS to traverse the component graph and assign groups
void dfs(int u) {
  vis[u] = 1, ans[++cnt] = u;
  for (int i : v[u])
    if (!vis[i])
      dfs(i);
}

// Solve one test case
inline void sol() {
  scanf("%d%d%d", &n1, &n2, &m), n = n1 + n2, dcnt = cnt = 0, idx = 1;
  for (int i = 1; i <= n; ++i)
    v[i].clear(), h[i] = dfn[i] = vis[i] = 0;
  while (m--)
    scanf("%d%d", &a, &b), add(a, b), add(b, a);
  tar(1, 0), dfs(1);
  for (int i = 1; i <= n1; ++i)
    printf("%d ", ans[i]);
  puts("");
  for (int i = n1 + 1; i <= n; ++i)
    printf("%d ", ans[i]);
  puts("");
}

int main() {
  scanf("%d", &T);
  while (T--)
    sol();
  return 0;
}


// https://github.com/VaHiX/CodeForces/