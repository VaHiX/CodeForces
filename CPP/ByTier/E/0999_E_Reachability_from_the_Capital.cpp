// Problem: CF 999 E - Reachability from the Capital
// https://codeforces.com/contest/999/problem/E

/*
Algorithm: Strongly Connected Components (SCC) + DFS
Approach:
1. Build the graph and find all nodes reachable from the capital s.
2. Find all strongly connected components (SCCs) in the graph.
3. Count the number of SCCs that are not reachable from the capital s.
4. The minimum number of new roads needed = number of such unreachable SCCs.

Time Complexity: O(n + m), where n is number of nodes and m is number of edges
Space Complexity: O(n + m), for storing the graph and auxiliary arrays

*/
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
using namespace std;
vector<int> G[5005]; // Adjacency list for the graph
int f[5005], cnt, a[5005], ans, n, m, s, u, v;

// DFS to traverse all reachable nodes from node x
void dfs(int x) {
  for (int i = 0; i < G[x].size(); ++i) {
    if (!f[G[x][i]]) // If not visited yet
      f[G[x][i]] = 1, dfs(G[x][i]); // Mark and recurse
  }
}

signed main() {
  cin >> n >> m >> s;
  while (m--) {
    cin >> u >> v;
    G[u].push_back(v); // Add directed edge u -> v
  }

  // First DFS to find all nodes and build reverse order of finishing times
  for (int i = 1; i <= n; ++i)
    if (!f[i])
      f[i] = 1, dfs(i), a[++cnt] = i; // Store nodes in finishing order

  // Reset visited array
  memset(f, 0, sizeof(f));
  f[s] = 1; // Mark capital as visited
  dfs(s); // Mark all nodes reachable from capital

  // Count the number of SCCs not reachable from capital
  for (int i = cnt; i; --i)
    if (!f[a[i]]) // If not visited in previous DFS
      f[a[i]] = 1, dfs(a[i]), ans++; // Count this SCC as unreachable

  cout << ans; // Output the minimum roads needed
}


// https://github.com/VaHiX/CodeForces/