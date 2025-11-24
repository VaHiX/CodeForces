// Problem: CF 1930 H - Interactive Mex Tree
// https://codeforces.com/contest/1930/problem/H

/*
Purpose: 
This code solves the interactive problem "H. Interactive Mex Tree" where Bob needs to find the MEX (minimum excludant) 
of values on the path between two nodes in a tree, using at most 5 queries per round.

Algorithms/Techniques:
- DFS-based numbering (dfn1, dfn2) to represent tree traversal orders
- Lowest Common Ancestor (LCA) technique to find path between nodes
- Binary search on the answer using min queries to determine the MEX efficiently
- Two permutations (p1, p2) are used to optimize the query strategy

Time Complexity: O(n log n + q * log n) where n is number of nodes and q is number of rounds
Space Complexity: O(n) for storing tree structure, DFS traversal information, and auxiliary arrays

*/
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
const int N = 1e5 + 5;
int T, n, q, dfn1[N], dfn2[N], t1, t2, dp[N], fa[N];
vector<int> e[N];

// First DFS to assign dfn1 and build path in tree
void dfs1(int x, int y) {
  dp[x] = dp[y] + 1, fa[x] = y;
  for (auto v : e[x])
    if (v != y)
      dfs1(v, x);
  dfn1[x] = ++t1;
  printf("%d ", x);
}

// Second DFS to assign dfn2 in reverse order to optimize queries
void dfs2(int x, int y) {
  reverse(e[x].begin(), e[x].end());
  for (auto v : e[x])
    if (v != y)
      dfs2(v, x);
  dfn2[x] = ++t2;
  printf("%d ", x);
}

// Function to perform a query to get minimum in a range
int ask(int o, int l, int r) {
  int x;
  printf("? %d %d %d\n", o, l, r);
  fflush(stdout);
  scanf("%d", &x);
  return x;
}

// Function to compute lowest common ancestor (LCA) of two nodes
int lca(int x, int y) {
  if (dp[x] > dp[y])
    swap(x, y);
  while (dp[y] > dp[x])
    y = fa[y];
  while (x != y)
    x = fa[x], y = fa[y];
  return x;
}

// Function to output the answer and verify it
void answer(int u) {
  int x;
  printf("! %d\n", u);
  fflush(stdout);
  scanf("%d", &x);
  assert(x == 1);
}

// Function to compute MEX for path between nodes x and y
void ask(int x, int y) {
  if (dfn1[x] > dfn1[y])
    swap(x, y);
  int z = lca(x, y);
  int mn = n;
  if (dfn1[x] > 1)
    mn = min(mn, ask(1, 1, dfn1[x] - 1));
  if (dfn1[z] < n)
    mn = min(mn, ask(1, dfn1[z] + 1, n));
  if (z == y) {
    if (dfn2[x] > 1)
      mn = min(mn, ask(2, 1, dfn2[x] - 1));
    return answer(mn);
  }
  if (dfn2[y] > 1)
    mn = min(mn, ask(2, 1, dfn2[y] - 1));
  int _x = x, _y = y;
  while (fa[x] != z)
    x = fa[x];
  while (fa[y] != z)
    y = fa[y];
  if (dfn1[x] + 1 < dfn1[_y])
    mn = min(mn, ask(1, dfn1[x] + 1, dfn1[_y] - 1));
  if (dfn2[y] + 1 < dfn2[_x])
    mn = min(mn, ask(2, dfn2[y] + 1, dfn2[_x] - 1));
  answer(mn);
}

// Main solve function for each test case
void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    e[i].clear();
  for (int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    e[x].push_back(y), e[y].push_back(x);
  }
  t1 = t2 = 0;
  dfs1(1, 0);
  putchar(10);
  dfs2(1, 0);
  putchar(10);
  fflush(stdout);
  for (int i = 1, x, y; i <= q; ++i) {
    scanf("%d%d", &x, &y);
    ask(x, y);
  }
}

int main() {
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/