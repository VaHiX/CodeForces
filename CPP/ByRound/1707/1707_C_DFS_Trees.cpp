// Problem: CF 1707 C - DFS Trees
// https://codeforces.com/contest/1707/problem/C

/*
Algorithm: This code determines which DFS-based spanning tree constructions yield a Minimum Spanning Tree (MST).
The algorithm performs the following steps:
1. Builds a DFS tree of the graph using Union-Find to detect edges that are not part of the DFS tree (back edges).
2. For each back edge, it identifies the lowest common ancestor and updates a counter array to track how many times each node contributes to the cycle.
3. Computes the final result by checking for each node whether it is part of an MST (based on number of back edges).

Time Complexity: O(n + m * α(n)) where α(n) is the inverse Ackermann function, nearly constant.
Space Complexity: O(n + m), for storing adjacency lists and auxiliary arrays.

*/

#include <stdio.h>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;
const int N = 1e5 + 7;
int f[N], d[N], a[N], s[N], vis[N], i, j, k, n, m;
vector<int> e[N], g[N];
vector<pair<int, int>> E;
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void dfs(int x, int fa) {
  d[x] = d[fa] + 1;
  for (auto &y : e[x])
    if (y != fa)
      dfs(y, x);
}
void dfs2(int x, int fa) {
  s[d[x]] = x;
  vis[x] = 1;
  for (auto &y : g[x]) {
    a[x]++;
    if (vis[y])
      a[1]++, a[s[d[y] + 1]]--;
    else
      a[y]++;
  }
  for (auto &y : e[x])
    if (y != fa)
      dfs2(y, x);
  vis[x] = 0;
}
void dfs3(int x, int fa) {
  a[x] += a[fa];
  for (auto &y : e[x])
    if (y != fa)
      dfs3(y, x);
}
int main() {
  for (scanf("%d%d", &n, &m), iota(f + 1, f + n + 1, 1), k = 1; k <= m; ++k) {
    scanf("%d%d", &i, &j);
    if (find(i) != find(j)) {
      e[i].push_back(j), e[j].push_back(i);
      f[find(i)] = find(j);
    } else
      E.push_back(make_pair(i, j));
  }
  dfs(1, 0);
  for (auto D : E) {
    if (d[D.first] < d[D.second])
      swap(D.first, D.second);
    g[D.first].push_back(D.second);
  }
  dfs2(1, 0);
  dfs3(1, 0);
  for (i = 1; i <= n; ++i)
    printf("%d", a[i] == m - n + 1);
  puts("");
}


// https://github.com/VaHiX/CodeForces/