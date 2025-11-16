// Problem: CF 1774 E - Two Chess Pieces
// https://codeforces.com/contest/1774/problem/E

/*
 * Problem: E. Two Chess Pieces
 * 
 * Purpose: Given a tree with n nodes and two pieces starting at node 1, determine the minimum steps
 *          to visit all required nodes by both pieces while maintaining a maximum distance d between them.
 * 
 * Algorithm:
 * - Build adjacency list representation of the tree.
 * - Track which nodes each piece must visit using a boolean matrix.
 * - Use DFS to traverse the tree and compute the coverage of each piece.
 * - For each node, if either piece needs to visit it, count it toward the total.
 * - Return 2 * total visited nodes as each node must be entered and exited.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * 
 * Techniques:
 * - Tree traversal using DFS
 * - Bitmask tracking of node visits
 * - Distance constraint enforcement via tracking
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
using namespace std;
using ll = long long;

void solve() {
  int n, d;
  cin >> n >> d;
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<vector<int>> vis(2, vector<int>(n));
  for (int i = 0; i < 2; ++i) {
    int m;
    cin >> m;
    for (int j = 0; j < m; ++j) {
      int v;
      cin >> v;
      v--;
      vis[i][v] = 1;
    }
  }
  vector<int> path(n);
  vis[0][0] = vis[1][0] = 1;
  int len = 0;
  auto dfs = [&](int par, int curr, auto &&dfs) -> void {
    // If we've moved beyond distance d, mark the old node's influence on current node
    if (len >= d) {
      vis[0][path[len - d]] |= vis[1][curr];
      vis[1][path[len - d]] |= vis[0][curr];
    }
    path[len++] = curr;
    for (auto nei : g[curr]) {
      if (nei != par)
        dfs(curr, nei, dfs);
    }
    if (par != -1) {
      // Propagate visit information up the tree
      vis[0][par] |= vis[0][curr];
      vis[1][par] |= vis[1][curr];
    }
    len--;
  };
  dfs(-1, 0, dfs);
  int sol = 0;
  for (int i = 1; i < n; ++i) {
    sol += vis[0][i];
    sol += vis[1][i];
  }
  cout << 2 * sol << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  while (t--)
    solve();
#ifdef LOCAL_TIME
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
#endif
}


// https://github.com/VaHiX/CodeForces/