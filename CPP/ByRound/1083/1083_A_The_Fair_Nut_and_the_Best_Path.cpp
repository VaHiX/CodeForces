// Problem: CF 1083 A - The Fair Nut and the Best Path
// https://codeforces.com/contest/1083/problem/A

/*
 * Problem: A. The Fair Nut and the Best Path
 * Algorithms/Techniques: Tree Dynamic Programming, DFS traversal
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Description:
 * Given a tree with n nodes, each node has a value w[i] representing the maximum
 * amount of gasoline that can be bought at that node. Each edge has a weight c
 * representing the cost (in liters) to traverse that edge. The goal is to find the
 * path in the tree such that the amount of gasoline at the end of the path is maximized.
 * The amount of gasoline decreases by the cost of traversing each edge, but can be
 * replenished at any node visited along the way.
 *
 * Approach:
 * Perform DFS on the tree rooted at node 1. For each node x, we calculate:
 * - dp[x]: maximum gas that can be achieved starting from node x and going down
 *   in one direction (to a leaf).
 * - At each node, we check all its children and update the global maximum answer.
 *   For two children, we consider paths through both of them to compute potential
 *   maximum for the current node.
 */

#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;

const int N = 3e5 + 10;
int T, n, tot, h[N]; // h: head of adjacency list
ll w[N], dp[N], ans = 0; // w: gas capacity in each node, dp: max gas from current node down
struct Edge {
  int v, nxt; // v: neighbor node, nxt: next edge index
  ll w;       // w: weight/cost of this edge
} e[N << 1]; // e: edge list (2 * n edges for undirected graph)

void add(int a, int b, ll c) {
  // Add edge from a to b with weight c
  e[++tot].v = b, e[tot].w = c, e[tot].nxt = h[a], h[a] = tot;
}

void dfs(int x, int fx) {
  // x: current node, fx: parent node
  dp[x] = w[x]; // Start with the gas available at current node
  ans = max(ans, w[x]); // Update global maximum with current node's gas
  
  for (int i = h[x], v; i; i = e[i].nxt) // Iterate through all neighbors of x
    if ((v = e[i].v) != fx) { // Skip parent to avoid going back
      dfs(v, x); // Recursively process child node
      
      // Update answer: best path that passes through current node and goes through two children
      ans = max(ans, dp[x] + dp[v] - e[i].w);
      
      // Update dp[x]: maximum gas achievable from x going down to one of its subtrees
      dp[x] = max(dp[x], dp[v] + w[x] - e[i].w);
    }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", w + i);
  for (int i = 1; i < n; i++) {
    int a, b;
    ll c;
    scanf("%d%d%lld", &a, &b, &c);
    add(a, b, c), add(b, a, c); // Add bidirectional edges
  }
  dfs(1, 0); // Start DFS from root node 1 with no parent (0)
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/codeForces/