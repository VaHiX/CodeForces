// Problem: CF 1763 F - Edge Queries
// https://codeforces.com/contest/1763/problem/F

/*
 * Problem: F. Edge Queries
 * 
 * Algorithm/Techniques:
 * - Tarjan's algorithm for finding biconnected components (BCCs)
 * - Lowest Common Ancestor (LCA) using binary lifting
 * - Preprocessing to count how many edges in BCCs are on paths between nodes
 * 
 * Time Complexity: O(n + m + q * log n)
 * Space Complexity: O(n + m)
 * 
 * The solution uses Tarjan's algorithm to decompose the graph into biconnected components,
 * then uses LCA with binary lifting to answer queries efficiently.
 * For each query (a, b), we count edges that belong to some path between a and b and 
 * removing them would still allow reachability between a and b. This is done by 
 * counting edges in the BCCs along the path from a to b using precomputed values.
 */

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 4e5 + 5;
vector<int> G[N], Tr[N];  // G: original graph, Tr: block-cut tree
int fa[N][20], dfn[N], low[N], dep[N], stk[N], col[N], pre[N], Eu[N], Ev[N];
int n, m, q, u, v, node, top, tim;

// Add edge to block-cut tree
void Add(int u, int v) { Tr[u].push_back(v), Tr[v].push_back(u); }

// Tarjan's algorithm to find biconnected components
void Tarjan(int u, int f) {
  dfn[u] = low[u] = ++tim;
  stk[++top] = u;
  for (int v : G[u])
    if (!dfn[v])
      Tarjan(v, u), low[u] = min(low[u], low[v]);
    else if (v != f)
      low[u] = min(low[u], dfn[v]);
  if (low[u] == dfn[u]) {
    node++;
    while (stk[top] != u)
      col[stk[top]] = node, Add(stk[top--], node);
    col[u] = node, Add(u, node);
    top--;
  }
}

// DFS traversal on block-cut tree to compute depths and ancestors
void dfs(int u, int f) {
  dep[u] = dep[f] + 1;
  fa[u][0] = f;
  pre[u] += pre[f];  // Propagate count from parent
  for (int i = 1; i <= 18; i++)
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (int v : Tr[u])
    if (v != f)
      dfs(v, u);
}

// Find LCA using binary lifting
int LCA(int u, int v) {
  if (u == v)
    return u;
  if (dep[u] < dep[v])
    swap(u, v);
  int d = dep[u] - dep[v];
  for (int i = 18; ~i; i--)
    if (d & (1 << i))
      u = fa[u][i];
  if (u == v)
    return u;
  for (int i = 18; ~i; i--)
    if (fa[u][i] ^ fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return fa[u][0];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v), G[u].push_back(v), G[v].push_back(u);
    Eu[i] = u, Ev[i] = v;
  }
  node = n;
  Tarjan(1, 0);
  for (int i = 1; i <= m; i++)
    if (col[Eu[i]] == col[Ev[i]])
      pre[col[Eu[i]]]++;  // Count edges in same BCC
    else
      Add(Eu[i], Ev[i]);  // Add edge to block-cut tree if not in same BCC
  dfs(1, 0);
  scanf("%d", &q);
  for (; q; q--) {
    scanf("%d%d", &u, &v);
    int L = LCA(u, v);
    printf("%d\n", pre[u] + pre[v] - pre[L] - pre[fa[L][0]]);  // Answer query using precomputed values
  }
}


// https://github.com/VaHiX/CodeForces/