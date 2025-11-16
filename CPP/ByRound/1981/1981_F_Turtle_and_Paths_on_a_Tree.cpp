// Problem: CF 1981 F - Turtle and Paths on a Tree
// https://codeforces.com/contest/1981/problem/F

/*
 * Problem: F. Turtle and Paths on a Tree
 * 
 * Purpose: 
 *   This code solves the problem of finding the minimum MEX value over all good sets of paths in a binary tree.
 *   A good set of paths covers each edge exactly once. The value of a set of paths is defined as the sum of 
 *   MEX values of all vertices on the paths. MEX is the smallest positive integer not present in the collection.
 *   
 * Algorithm:
 *   - Use dynamic programming on trees (tree DP)
 *   - For each node, we compute for each possible MEX value (up to 3800) the minimum cost to cover all edges
 *     in the subtree rooted at this node, with the constraint that paths may start or end at this node.
 *   - The DP state is based on whether we have a path ending at the node or not.
 *   - We process each node in a bottom-up manner using DFS.
 *   
 * Time Complexity: O(n * M), where n is the number of nodes and M is the maximum value used (3800).
 * Space Complexity: O(n * M) for DP table.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
const int N = 25000 + 10, M = 3800, INF = 1e9;
int a[N], dp[N][M], L[2][M], R[2][M];
vector<int> g[N];

/**
 * DFS function to compute minimum cost for paths in subtree rooted at u.
 * @param u: current node in the tree.
 */
void dfs(int u) {
  // Base case: leaf node
  if (g[u].size() == 0) {
    for (int i = 1; i < M; i++) {
      if (i == a[u]) {
        dp[u][i] = INF;
      } else {
        dp[u][i] = 0;
      }
    }
    return;
  }
  
  // Case 1: Node with one child
  if (g[u].size() == 1) {
    int c1 = g[u][0];
    dfs(c1);
    int ans = INF;
    for (int i = 1; i < M; i++) {
      if (i == a[u]) {
        dp[u][i] = INF;
      } else {
        ans = min(ans, dp[c1][i] + i);  // Add cost of path through c1 node
      }
    }
    for (int i = 1; i < M; i++) {
      if (i != a[u])
        dp[u][i] = min(dp[c1][i], ans);  // Consider both cases: no path, or path through child
    }
    if (u == 1) {
      printf("%d\n", ans);
    }
    return;
  } 
  // Case 2: Node with two children (binary tree)
  else if (g[u].size() == 2) {
    int c1 = g[u][0], c2 = g[u][1];
    dfs(c1);
    dfs(c2);
    int lmin = INF, rmin = INF;
    int merge = INF;
    for (int i = 1; i < M; i++) {
      if (i != a[u]) {
        lmin = min(lmin, dp[c1][i] + i);  // Cost if we include path through c1
        rmin = min(rmin, dp[c2][i] + i);  // Cost if we include path through c2
        merge = min(merge, dp[c1][i] + dp[c2][i] + i);  // Merge cost from both children
      }
    }
    for (int i = 1; i < M; i++) {
      if (i != a[u]) {
        dp[u][i] = min(merge, min(dp[c1][i] + rmin, dp[c2][i] + lmin));  // Choose minimum cost
      } else {
        dp[u][i] = INF;
      }
    }
    if (u == 1) {
      printf("%d\n", min(merge, lmin + rmin));  // Output minimum cost for root
    }
  }
}

/**
 * Solve function for a single test case.
 */
void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i <= n; i++)
    g[i].clear();
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int u = 2; u <= n; u++) {
    int p;
    scanf("%d", &p);
    g[p].push_back(u);  // Build adjacency list
  }
  dfs(1);
}

int main() {
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/