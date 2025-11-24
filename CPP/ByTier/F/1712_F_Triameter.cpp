// Problem: CF 1712 F - Triameter
// https://codeforces.com/contest/1712/problem/F

// # Triameter Problem Solution

// This code solves the problem of finding the diameter of a tree after adding
// edges between all leaf nodes with a given weight. The approach uses tree
// decomposition techniques including DFS traversal and dynamic programming on
// trees.

// ## Algorithms/Techniques:
// - Tree DFS traversal for computing depths and subtree information
// - Heavy-light decomposition with centroid decomposition principles
// - Dynamic Programming on trees to compute diameters after edge additions
// - Optimized tree traversal to efficiently process multiple queries

// ## Time and Space Complexity:
// - Time Complexity: O(n * q) where n is the number of vertices and q is the
// number of queries
// - Space Complexity: O(n) for storing graph and auxiliary arrays

#include <algorithm>
#include <stdio.h>

using namespace std;
int n, m, h[1000005], idx, son[1000005], len[1000005], lv[1000005], F[1000005],
    dep[1000005], *f[1000005], *f_ = F, x, ans;
struct node {
  int from, v;
} G[2000005];
void make(int u, int v) {
  G[++idx] = {h[u], v};
  h[u] = idx;
}
void dfs1(int u, int fa) {
  len[u] = 1;
  if (!G[h[u]].from)
    lv[u] = 0;
  else
    lv[u] = n + 1;
  for (int i = h[u]; i; i = G[i].from) {
    int v = G[i].v;
    if (v != fa) {
      dfs1(v, u);
      if (len[v] + 1 > len[u])
        son[u] = v, len[u] = len[v] + 1;
      lv[u] = min(lv[u], lv[v] + 1);
    }
  }
}
void dfs2(int u, int fa, int anc, int deep) {
  for (int i = h[u]; i; i = G[i].from) {
    int v = G[i].v;
    lv[u] = min(lv[u], lv[v] + 1);
  }
  dep[u] = deep, f[u] = f_, f_++;
  if (son[u])
    dfs2(son[u], u, anc, deep + 1);
  for (int i = h[u]; i; i = G[i].from) {
    int v = G[i].v;
    if (v != fa && v != son[u])
      dfs2(v, u, v, 0);
  }
}
void dfs3(int u, int fa) {
  if (son[u])
    dfs3(son[u], u);
  f[u][0] = lv[u];
  while (len[u] - 1 >= ans + 1 && f[u][0] + f[u][ans + 1] + x > ans)
    ans++;
  if (len[u] > 1)
    f[u][0] = max(f[u][0], f[u][1]);
  for (int i = h[u]; i; i = G[i].from) {
    int v = G[i].v;
    if (v != fa && v != son[u]) {
      dfs3(v, u);
      for (int j = min(len[v] - 1, ans); j >= 0; j--)
        while (len[u] - 1 >= ans - j && f[v][j] + f[u][ans - j] + x > ans)
          ans++;
      for (int j = len[v] - 1; j >= 0; j--)
        f[u][j + 1] = max(f[u][j + 1], f[v][j]);
      f[u][0] = max(f[u][0], f[u][1]);
    }
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int fa;
    scanf("%d", &fa);
    make(fa, i), make(i, fa);
  }
  dfs1(1, 0);
  dfs2(1, 0, 1, 0);
  scanf("%d", &m);
  while (m--) {
    ans = 0;
    scanf("%d", &x);
    dfs3(1, 0);
    printf("%d ", ans);
  }
}

// https://github.com/VaHiX/CodeForces/