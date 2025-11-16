// Problem: CF 1805 D - A Wide, Wide Graph
// https://codeforces.com/contest/1805/problem/D

/*
 * Problem: D. A Wide, Wide Graph
 * Algorithm: Tree diameter and centroid decomposition using BFS/DFS traversal
 * 
 * Approach:
 * - For each node, compute the maximum distance to any leaf (dis1) and second maximum distance (dis2)
 * - Use two DFS passes:
 *   1. First DFS (dfs): compute diameter-related info from root
 *   2. Second DFS (pushdown): propagate info to all nodes using parent info
 * - Count how many nodes are at each distance from their furthest leaf
 * - Process backwards to count number of components for each k
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <iostream>

using namespace std;
const int N = 101000 << 1;
int n, x, y;
int efirst[N], enext[N], eend[N], efn;

// Function to add an undirected edge to the adjacency list
void addedge(int x, int y) {
  efn++;
  eend[efn] = y;
  enext[efn] = efirst[x];
  efirst[x] = efn;
  efn++;
  eend[efn] = x;
  enext[efn] = efirst[y];
  efirst[y] = efn;
}

// Arrays to store distances and source node for diameter calculation
int dis1[N], dis2[N], source[N];
int ans[N];

// First DFS to compute maximum and second maximum distances from each node
void dfs(int x, int fa) {
  dis1[x] = 0;
  source[x] = -1;
  for (int h = efirst[x]; h; h = enext[h]) {
    int y = eend[h];
    if (y == fa) continue;
    dfs(y, x);
    // Update the max and second max distances
    if (dis1[y] + 1 > dis1[x]) {
      dis2[x] = dis1[x];
      dis1[x] = dis1[y] + 1;
      source[x] = y;
    } else if (dis1[y] + 1 > dis2[x]) {
      dis2[x] = dis1[y] + 1;
    }
  }
}

// Second DFS to propagate information from parent to child
void pushdown(int x, int fa) {
  if (fa != -1) {
    // Update distances based on parent's info
    if (source[fa] != x) {
      if (dis1[fa] + 1 >= dis1[x]) {
        dis1[x] = dis1[fa] + 1;
        source[x] = fa;
      } else if (dis1[fa] + 1 >= dis2[x])
        dis2[x] = dis1[fa] + 1;
    } else if (dis2[fa] + 1 >= dis1[x]) {
      dis1[x] = dis2[fa] + 1;
      source[x] = fa;
    } else if (dis2[fa] + 1 >= dis2[x])
      dis2[x] = dis2[fa] + 1;
  }
  for (int h = efirst[x]; h; h = enext[h]) {
    int y = eend[h];
    if (y == fa) continue;
    pushdown(y, x);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &x, &y);
    addedge(x, y);
  }
  dfs(1, -1);
  pushdown(1, -1);
  
  // Count how many nodes are at distance d from their furthest leaf
  for (int i = 1; i <= n; i++) {
    ans[dis1[i]]++;
  }
  
  // Accumulate from right to left to get total count >= k
  for (int i = n - 1; i >= 1; i--)
    ans[i] += ans[i + 1];
  
  // Output answer for each k from 1 to n
  for (int i = 1; i <= n; i++)
    printf("%d ", n - ans[i] + (ans[i] != 0));
  printf("\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/