// Problem: CF 902 B - Coloring a Tree
// https://codeforces.com/contest/902/problem/B

/*
 * Problem: B. Coloring a Tree
 * 
 * Purpose: Given a rooted tree and target colors for each node, find the minimum number 
 *          of operations to color the tree. Each operation allows coloring an entire 
 *          subtree with a single color.
 * 
 * Algorithm: 
 *   - Perform a DFS traversal from the root.
 *   - For each node, check if its color matches the target color.
 *   - If not, increment the operation count and update the color.
 *   - Propagate the color to all children nodes (since they are in the same subtree).
 *   - This greedy approach ensures minimal steps by coloring from top to bottom.
 * 
 * Time Complexity: O(n) where n is the number of nodes. Each node is visited once.
 * Space Complexity: O(n) for storing adjacency list and recursion stack.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 10010
#define inf 1000000000
using namespace std;
int n, m, cnt;
bool vis[N];
int rc[N], col[N]; // rc = required color, col = current color
vector<int> adj[N]; // adjacency list for tree

// DFS to traverse tree and count operations
void dfs(int s) {
  vis[s] = 1; // Mark current node as visited
  
  // If current node's color differs from target color, we need a coloring operation
  if (col[s] != rc[s]) {
    col[s] = rc[s]; // Update the color to target
    cnt++; // Increment operation count
    
    // Propagate the new color to all children
    for (int e : adj[s]) {
      if (!vis[e])
        col[e] = col[s];
    }
  } else {
    // If colors match, still propagate to children
    for (int e : adj[s]) {
      if (!vis[e])
        col[e] = col[s];
    }
  }
  
  // Continue DFS to all unvisited children
  for (int e : adj[s]) {
    if (!vis[e])
      dfs(e);
  }
}

int main() {
  int i, j, k;
  int t, s;
  cnt = 0;
  scanf("%d", &n);
  
  // Build adjacency list (tree is bidirectional)
  for (i = 2; i <= n; i++) {
    scanf("%d", &m);
    adj[i].push_back(m);
    adj[m].push_back(i);
  }
  
  memset(vis, 0, sizeof(vis));
  memset(col, 0, sizeof(col));
  
  // Read target colors
  for (i = 1; i <= n; i++)
    scanf("%d", &rc[i]);
  
  dfs(1); // Start DFS from root (node 1)
  printf("%d\n", cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/