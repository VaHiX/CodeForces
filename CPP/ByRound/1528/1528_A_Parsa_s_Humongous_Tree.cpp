// Problem: CF 1528 A - Parsa's Humongous Tree
// https://codeforces.com/contest/1528/problem/A

/*
 * Problem: Parsa's Humongous Tree
 * Description:
 *   Given a tree with n vertices, each vertex v has a range [l_v, r_v].
 *   Assign an integer a_v in that range such that the sum of |a_u - a_v| over all edges (u,v)
 *   is maximized.
 *
 * Algorithm:
 *   This is a tree dynamic programming problem. For each node,
 *   we compute two values:
 *   f[x][0]: maximum beauty when we assign a value to x such that it's in [l[x], r[x]] and
 *             the subtree rooted at x has its optimal assignment where the root of subtree has
 *             the same value chosen from [l[x], r[x]].
 *   f[x][1]: similar but the root can choose any value from [l[x], r[x]].
 *
 *   We do a DFS traversal and for each node, we consider all children,
 *   we calculate what's the maximum possible beauty gain from that child
 *   based on the choice of values in range [l[x], r[x]] vs [l[y], r[y]]
 *   by taking into account the absolute difference between values.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for adjacency list and DP arrays
 */

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
const int N = 1e6 + 3;
int l[N], r[N];
long long f[N][2];
basic_string<int> g[N];

// DFS to compute maximum beauty for subtree rooted at x
void dfs(int x, int y) {
  // Initialize DP values for current node
  f[x][0] = f[x][1] = 0;
  
  // Traverse all children (neighbors except parent)
  for (int i : g[x])
    if (i != y) {
      // Recursively calculate subtree beauty
      dfs(i, x);
      
      // Update DP values:
      // For node x choosing value from [l[x], r[x]]
      // We either choose a value from [l[x], r[x]] that matches the child's choice
      // or we choose a value that maximizes current edge contribution.
      f[x][0] += max(f[i][0] + abs(l[x] - l[i]), f[i][1] + abs(l[x] - r[i]));
      f[x][1] += max(f[i][0] + abs(r[x] - l[i]), f[i][1] + abs(r[x] - r[i]));
    }
}

int main() {
  int T, n, i, j, k;
  scanf("%d", &T);
  
  while (T--) {
    scanf("%d", &n);
    
    // Clear adjacency list
    for (i = 1; i <= n; ++i)
      g[i].clear();
      
    // Read ranges for each vertex
    for (i = 1; i <= n; ++i)
      scanf("%d%d", l + i, r + i);
      
    // Build adjacency list from edges
    for (i = 1; i < n; ++i) {
      scanf("%d%d", &j, &k);
      g[j] += k;
      g[k] += j;
    }
    
    // Start DFS from root (node 1)
    dfs(1, 0);
    
    // Output result
    cout << max(f[1][0], f[1][1]) << '\n';
  }
  
  return 0;
}


// https://github.com/VaHiX/codeForces/