// Problem: CF 802 K - Send the Fool Further! (medium)
// https://codeforces.com/contest/802/problem/K

/*
Algorithm: Tree Dynamic Programming with Greedy Selection
Techniques: DFS, Sorting, Greedy, Tree DP

Time Complexity: O(n log n) due to sorting in DFS traversal
Space Complexity: O(n) for storing tree structure and DP states

This solution uses a tree dynamic programming approach to compute the maximum cost
of tickets needed in the worst-case scenario, where each node can be visited at most k times.
The core idea is to process each node's children and decide how many edges to "buy"
based on the cost of edges and the number of times we can visit nodes.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
struct node {
  int to, next, dis;
} a[250001];
struct nood {
  int w, bh;
} s[200001];
int n, k, cnt, g[200001], f[200001][2], size[200001], sum[200001];

// Build adjacency list representation of the tree
void build(int from, int to, int dis) {
  a[++cnt].to = to;
  a[cnt].next = g[from];
  a[cnt].dis = dis;
  g[from] = cnt;
}

// Compare function for sorting edges by weight in descending order
bool cmp(nood x, nood y) { return x.w > y.w; }

// DFS traversal to compute optimal ticket selection for subtree
void dfs(int u, int fa) {
  // Traverse all children of current node u
  for (int i = g[u]; i; i = a[i].next) {
    int v = a[i].to;
    if (v != fa) {
      dfs(v, u);
    }
  }
  
  // Prepare data for current node's children
  int t = 0;
  for (int i = g[u]; i; i = a[i].next) {
    int v = a[i].to;
    if (v != fa) {
      // Increment the cost to reach child node via this edge
      f[v][1] += a[i].dis;
      f[v][0] += a[i].dis;
      t++;
      s[t].w = f[v][0];
      s[t].bh = v;
    }
  }
  
  // Sort children by cost in descending order
  sort(s + 1, s + t + 1, cmp);
  
  // Compute prefix sums for efficient range queries
  for (int i = 1; i <= t; i++)
    sum[i] = sum[i - 1] + s[i].w;
    
  // Compute max cost to visit node u at most k-1 times
  f[u][0] = sum[min(k - 1, t)];
  
  // Base case: if no children, return
  if (t == 0) {
    return;
  }
  
  // Try selecting different numbers of edges (up to k) to buy
  for (int i = 1; i <= k; i++) {
    // Calculate cost of buying `i` cheapest edges plus optimal cost from remaining subtree
    f[u][1] = max(f[u][1], sum[min(k, t)] - s[i].w + f[s[i].bh][1]);
    if (i >= t) {
      break;
    }
  }
  
  // For cases where we have more children than k, handle remaining edge costs
  for (int i = k + 1; i <= t; i++) {
    f[u][1] = max(f[u][1], sum[k - 1] + f[s[i].bh][1]);
  }
}

int main() {
  int x, y, z;
  scanf("%d%d", &n, &k);
  
  // Read edges and build tree
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &x, &y, &z);
    x++;
    y++;
    build(x, y, z);
    build(y, x, z);
  }
  
  // Start DFS from root (node 1)
  dfs(1, 0);
  
  // Output the result
  printf("%d", f[1][1]);
  return 0;
}


// https://github.com/VaHiX/CodeForces/