// Problem: CF 1822 F - Gardening Friends
// https://codeforces.com/contest/1822/problem/F

/*
Flower Box:
Purpose: This code solves the problem of maximizing profit from a tree by choosing the optimal root. 
         The profit is defined as the cost of the tree (maximum distance from root to any vertex) minus 
         the cost of operations (number of moves to change root, each costing 'c').

Algorithms/Techniques:
1. Tree Diameter Computation using DFS (two-pass DFS technique):
   - First DFS to compute the longest path from each node to its descendants.
   - Second DFS to propagate the longest path information to children.

Time Complexity: O(N) for each test case, where N is the number of vertices.
Space Complexity: O(N) for storing tree edges and auxiliary arrays.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

#define fi first
#define se second
#define mm(a, b) memset(a, b, sizeof(a))
#define pb push_back
#define ls (u << 1)
#define rs (u << 1 | 1)
#define PI acos(-1)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int N = 400005;
int n, k, c, e[N], ne[N], h[N], idx;
int f[N][2], son[N][2], d[N];

// First DFS to compute the longest path in the tree from root down (for each node)
void dfs1(int u, int fa) {
  for (int i = h[u]; i != -1; i = ne[i]) {
    int v = e[i];
    if (v == fa)
      continue;
    d[v] = d[u] + 1;
    dfs1(v, u);
    if (f[v][0] + 1 > f[u][0]) {
      f[u][1] = f[u][0];
      son[u][1] = son[u][0];
      f[u][0] = f[v][0] + 1;
      son[u][0] = v;
    } else if (f[v][0] + 1 > f[u][1]) {
      f[u][1] = f[v][0] + 1;
      son[u][1] = v;
    }
  }
}

// Second DFS to update the longest paths for children nodes
void dfs2(int u, int fa) {
  for (int i = h[u]; i != -1; i = ne[i]) {
    int v = e[i];
    if (v == fa)
      continue;
    int x = (son[u][0] == v) ? f[u][1] : f[u][0];
    if (x + 1 > f[v][0]) {
      f[v][1] = f[v][0];
      son[v][1] = son[v][0];
      f[v][0] = x + 1;
      son[v][0] = u;
    } else if (x + 1 > f[v][1]) {
      f[v][1] = x + 1;
      son[v][1] = u;
    }
    dfs2(v, u);
  }
}

// Add edge to adjacency list
void add(int u, int v) { 
  e[++idx] = v, ne[idx] = h[u], h[u] = idx; 
}

// Main function for a single test case
void konbi() {
  scanf("%d%d%d", &n, &k, &c);
  idx = 0;
  for (int i = 1; i <= n; i++) {
    h[i] = -1;
    f[i][0] = f[i][1] = 0;
    son[i][0] = son[i][1] = 0;
  }
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v);
    add(v, u);
  }
  dfs1(1, 0);
  dfs2(1, 0);
  int mx = 0;
  for (int i = 1; i <= n; i++)
    mx = max(mx, d[i]);
  LL res = 1ll * mx * k;
  for (int i = 1; i <= n; i++) {
    res = max(res, 1ll * k * f[i][0] - 1ll * c * d[i]);
  }
  printf("%lld\n", res);
}

int main() {
  int tt;
  cin >> tt;
  while (tt--)
    konbi();
}


// https://github.com/VaHiX/CodeForces/