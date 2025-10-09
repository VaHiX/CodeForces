// Problem: CF 2062 E1 - The Game (Easy Version)
// https://codeforces.com/contest/2062/problem/E1

/*
 * Problem: E1. The Game (Easy Version)
 * Algorithms/Techniques: DFS traversal, preprocessing with prefix/suffix max arrays,
 *                        Tree DFS order (Euler Tour), Optimization for win condition check.
 *
 * Time Complexity: O(n) per test case, amortized over all test cases.
 * Space Complexity: O(n) for graph storage, DFS stack, and auxiliary arrays.
 *
 * Purpose:
 * This code determines a node that Cirno can choose in the first turn such that she wins
 * the game assuming both players play optimally. It uses concepts of DFS traversal on a tree,
 * to compute an Euler tour (preorder/postorder), then checks for valid win conditions using
 * prefix and suffix max arrays to efficiently determine which nodes lead to a winning move.
 */

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 4e5 + 5;
vector<int> g[N];         // Adjacency list representation of the tree
int w[N], dfn[N], nfd[N], pre[N], suf[N], low[N], n; // Node weights, DFS numbers, etc.
bool vis[N];              // Visited array for DFS
int id;
void dfs(int u) {
  vis[u] = 1;             // Mark node as visited
  dfn[u] = ++id;          // Assign DFS number to node u (preorder)
  nfd[id] = u;            // Store node in Euler tour order
  for (auto v : g[u]) {   // For each neighbor
    if (vis[v])           // Skip if already visited
      continue;
    dfs(v);               // Recursively visit unvisited neighbors
  }
  low[u] = id;            // Assign low value as end of subtree in DFS order
}

int main() {
  int T;
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    id = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
      g[i].clear();
      vis[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      cin >> w[i];        // Read the weight of each node
    }
    for (int i = 1; i < n; i++) { // Read all edges to build tree structure
      int a, b;
      cin >> a >> b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    dfs(1);               // Start DFS from root node 1

    // Build prefix max array - maximum weight up to current point in DFS order
    for (int i = 1; i < n; i++)
      pre[i] = max(pre[i - 1], w[nfd[i]]);

    // Build suffix max array - maximum weight from current point onwards in DFS order
    suf[n + 1] = 0;
    for (int i = n; i >= 1; i--)
      suf[i] = max(suf[i + 1], w[nfd[i]]);

    int mx = 0;           // Will store index of best node to choose

    // Scan each node to evaluate if choosing it leads to a forced win for Cirno
    for (int i = 1; i <= n; i++) {
      // Check if the max value among ancestors + descendants > w[i] and also greater than previous best
      if (max(pre[dfn[i] - 1], suf[low[i] + 1]) > w[i] && w[i] > w[mx])
        mx = i;
    }

    cout << mx << '\n';   // Output the winning node or 0 if none found
  }
}


// https://github.com/VaHiX/codeForces/