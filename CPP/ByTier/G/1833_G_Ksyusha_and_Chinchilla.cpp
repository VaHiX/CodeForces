// Problem: CF 1833 G - Ksyusha and Chinchilla
// https://codeforces.com/contest/1833/problem/G

/*
Purpose: This code solves the problem of determining whether a tree can be cut into branches (paths of length 2), and if so, which edges to cut.

Algorithm:
- The solution uses a DFS traversal of the tree to determine valid cuts.
- A branch is a path of exactly 3 vertices (i.e., 2 edges).
- For a valid decomposition into branches, each subtree must have a size that is a multiple of 3 or can be trimmed down to size 3.
- During DFS, we track subtree sizes and collect edges that need to be cut to form valid 3-vertex components.

Time Complexity: O(n) per test case, due to single DFS traversal
Space Complexity: O(n) for storing adjacency list and auxiliary data structures

Techniques:
- Tree DFS with post-order processing
- Edge tracking and component size calculation
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 2e5 + 10;
int n, head[N], tot = 1;
struct edge {
  int to, nxt, val;
} mp[N * 2];
void add(int x, int y, int z) {
  mp[++tot] = {y, head[x], z};
  head[x] = tot;
}
int siz[N];
vector<int> _;
bool dfs(int x, int fa) {
  bool ans = 1;
  siz[x] = 1;
  for (int i = head[x]; i; i = mp[i].nxt) {
    int u = mp[i].to, id = mp[i].val;
    if (u == fa)
      continue;
    ans &= dfs(u, x);
    if (siz[u] == 3)
      siz[u] = 0, _.push_back(id); // Mark edge if subtree is exactly 3 nodes
    if (siz[u] > 3)
      return 0; // Invalid if subtree size > 3
    siz[x] += siz[u]; // Accumulate size of subtree
  }
  if (x == 1 && siz[x] != 3)
    return 0; // Root must end up with exactly 3 nodes in final tree
  return ans;
}
void Do() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    head[i] = 0;
  for (int i = 1; i <= tot; i++)
    mp[i] = {0, 0, 0};
  tot = 1;
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    add(x, y, i), add(y, x, i); // Add bidirectional edges with index
  }
  _.clear();
  if (!dfs(1, 0)) {
    puts("-1");
  } else {
    cout << _.size() << '\n';
    for (int u : _)
      cout << u << " ";
    puts("");
  }
}
int main() {
  int t;
  cin >> t;
  while (t--)
    Do();
  return 0;
}


// https://github.com/VaHiX/CodeForces/