// Problem: CF 2019 E - Tree Pruning
// https://codeforces.com/contest/2019/problem/E

/*
E. Tree Pruning
Algorithms/Techniques: DFS traversal, tree pruning, prefix sums

Time Complexity: O(n) per test case
Space Complexity: O(n) for the tree structure and auxiliary arrays

Problem Description:
Given a tree rooted at node 1, we need to remove leaves (non-root nodes with degree 1)
to make all remaining leaves at the same distance from the root.
The goal is to find the minimum number of operations (removals) required.

Approach:
- First, we compute the depth and maximum depth for each node during DFS.
- Then, we count how many nodes exist at each depth level and maximum depth level.
- Using prefix sums on these counts, we calculate the optimal cut point
  that minimizes the number of operations to make all leaves have the same depth.
*/

#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;
#define fuck puts("fuck");
const int N = 1e6 + 10, inf = 0x3f3f3f3f;
int n;
int cnt, head[N], nxt[N], to[N]; // Graph representation using adjacency list
int dep[N], mxd[N]; // dep[u] stores depth of node u; mxd[u] stores max depth in subtree rooted at u
int cdep[N], cmxd[N]; // cdep[i]: count of nodes at depth i; cmxd[i]: count of nodes with max depth i
int ans;

void add(int u, int v) {
  nxt[++cnt] = head[u]; // Add edge from u to v
  head[u] = cnt;
  to[cnt] = v;
}

void dfs(int u, int ff) {
  for (int i = head[u]; i; i = nxt[i]) { // Iterate over all neighbors of u
    if (to[i] == ff) // Skip parent node
      continue;
    mxd[to[i]] = dep[to[i]] = dep[u] + 1; // Set depth and initialize max depth for child
    dfs(to[i], u); // Recursively process child
    mxd[u] = max(mxd[u], mxd[to[i]]); // Update max depth of current node based on children
  }
}

void solve() {
  scanf("%d", &n);
  cnt = 0;
  for (int i = 1; i <= n; ++i)
    head[i] = cdep[i] = cmxd[i] = 0; // Initialize arrays
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    add(u, v), add(v, u); // Add bidirectional edges
  }
  mxd[1] = dep[1] = 1; // Root node has depth 1
  dfs(1, 0); // Start DFS from root
  for (int i = 1; i <= n; ++i)
    cdep[dep[i]]++, cmxd[mxd[i]]++; // Count nodes by depth and max depth
  for (int i = 1; i <= n; ++i)
    cdep[i] += cdep[i - 1], cmxd[i] += cmxd[i - 1]; // Compute prefix sums
  ans = inf;
  for (int i = 1; i <= n; ++i)
    ans = min(ans, cmxd[i - 1] + cdep[n] - cdep[i]); // Try all possible cut points
  printf("%d\n", ans);
}

signed main() {
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/codeForces/