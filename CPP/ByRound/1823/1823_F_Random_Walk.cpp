// Problem: CF 1823 F - Random Walk
// https://codeforces.com/contest/1823/problem/F

/*
 * Problem: Random Walk on Tree
 * Algorithms/Techniques: Tree DFS, Dynamic Programming on Tree
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * This solution computes the expected number of times each node is visited
 * during a random walk from node s to node t in a tree.
 * 
 * The approach uses two DFS traversals:
 * 1. First DFS to compute depths and parent relationships
 * 2. Second DFS to compute expected values using dynamic programming
 * 
 * Key insight: For each node, the expected value is influenced by how many
 * paths lead to it during the random walk process.
 */

#include <stdio.h>
#include <fstream>

using namespace std;
struct edge {
  int y;
  edge *next;
};
edge *new_edge() {
  static edge a[400005];
  static int top = 0;
  return &a[top++];
}
edge *li[200005];
void inserts(int x, int y) {
  edge *t = new_edge();
  t->y = y;
  t->next = li[x];
  li[x] = t;
}
void insert_edge(int x, int y) {
  inserts(x, y);
  inserts(y, x);
}
int fa[200005];
int ans[200005];
int depth[200005];
void dfs(int x) {
  edge *t;
  for (t = li[x]; t != 0; t = t->next) {
    if (t->y == fa[x]) {
      continue;
    }
    fa[t->y] = x;
    depth[t->y] = depth[x] + 1;
    dfs(t->y);
  }
}
const int modo = 998244353;
void dfs2(int x, int y) {
  edge *t;
  ans[x] = y;
  for (t = li[x]; t != 0; t = t->next) {
    if (t->y == fa[x]) {
      continue;
    }
    ans[x] += y;
    ans[x] %= modo;
    if (ans[t->y] != 0) {
      continue;
    }
    dfs2(t->y, y);
  }
}
int main() {
#ifdef absi2011
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n, s, t;
  scanf("%d%d%d", &n, &s, &t);
  s--;
  t--;
  int i;
  for (i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    insert_edge(x, y);
  }
  dfs(t);
  for (i = s; i != t; i = fa[i]) {
    dfs2(i, depth[i]);
  }
  ans[t] = 1;
  for (i = 0; i < n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/