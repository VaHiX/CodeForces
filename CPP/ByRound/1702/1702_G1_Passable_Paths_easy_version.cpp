// Problem: CF 1702 G1 - Passable Paths (easy version)
// https://codeforces.com/contest/1702/problem/G1

/*
 * Problem: Passable Paths in a Tree
 * 
 * Algorithm:
 * - The problem checks if a given set of vertices forms a passable path in a tree.
 * - A set is passable if there exists a simple path in the tree that visits all vertices of the set.
 * - The approach uses DFS on the tree and counts how many "branches" (subtrees with selected vertices) 
 *   are connected to a node. A node is valid if it has at most one such branch, except for special cases.
 * - The key insight is that a valid path in a tree connecting all selected vertices can be seen as a 
 *   subtree where the number of leaves with selected vertices is at most 2.
 * 
 * Time Complexity: O(n + sum(k)) where n is the number of nodes and sum(k) is the total size of all query sets.
 * Space Complexity: O(n) for the adjacency list and auxiliary arrays.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 2e5 + 5;
int sum[maxn], k;                    // sum[x] stores number of selected vertices in subtree of x
bool vis[maxn], f;                   // vis[x] marks if vertex x is selected, f tracks if path is valid
vector<int> ed[maxn];                // adjacency list for the tree

// DFS to determine if selected vertices form a valid passable path
void dfs(int x, int l) {
  int path = 0;                      // number of subtrees containing selected vertices
  sum[x] = vis[x];                   // initialize sum with 1 if current vertex is selected
  for (int y : ed[x]) {
    if (y == l)                      // skip parent to avoid going back
      continue;
    dfs(y, x);                       // recursive DFS on child
    sum[x] += sum[y];                // accumulate selected vertices in subtree  
    path += (sum[y] ? 1 : 0);        // count subtrees that have selected vertices
  }
  // Check if current node is valid:
  // - if path <= 1, it's valid 
  // - special case: path == 2 and all vertices in this subtree are selected (entire set is on path)
  f &= (path <= 1 || (path == 2 && k == sum[x]));
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &k);
    memset(vis, 0, sizeof(vis)), f = 1;  // reset for each query
    for (int j = 1; j <= k; j++) {
      int x;
      scanf("%d", &x);
      vis[x] = 1;  // mark selected vertices
    }
    dfs(1, 0);     // start DFS from root (node 1)
    puts(f ? "YES" : "NO");  // output result
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/