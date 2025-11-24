// Problem: CF 1697 E - Coloring
// https://codeforces.com/contest/1697/problem/E

/*
Purpose: This code solves a graph coloring problem with specific distance constraints.
         It determines the number of valid color assignments to points such that
         distance-based constraints are satisfied for all ordered triples of points.

Algorithms/Techniques:
- Graph traversal (DFS) to find connected components
- Dynamic Programming with memoization
- Modular arithmetic for large number handling

Time Complexity: O(n^3) - due to nested loops for computing minimum distances and graph construction
Space Complexity: O(n^2) - for storing the adjacency list and auxiliary arrays

The algorithm works by:
1. Building a graph where nodes are connected if they have the minimum distance to a given node
2. Identifying connected components via DFS
3. Applying dynamic programming on component sizes to count valid colorings
4. Combining results using factorial multiplication for overall permutations

*/

#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 110, mod = 998244353;
int n, x[N], y[N];
long long dp[N];
bool vis[N], del[N];
vector<int> g[N], tmp;
int dis(int i, int j) { return abs(x[i] - x[j]) + abs(y[i] - y[j]); }
int dfs(int x) {
  vis[x] = 1;
  tmp.push_back(x);
  int sum = g[x].size();
  for (int i = 0; i < g[x].size(); i++) {
    int y = g[x][i];
    if (!vis[y]) {
      sum += dfs(y);
    }
  }
  return sum;
}
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }
  // Build adjacency list based on minimum distance
  for (int i = 1; i <= n; i++) {
    int minDis = 1e9;
    for (int j = 1; j <= n; j++) {
      if (i == j)
        continue;
      minDis = min(minDis, dis(i, j));
    }
    for (int j = 1; j <= n; j++) {
      if (minDis == dis(i, j)) {
        g[i].push_back(j);
      }
    }
  }
  dp[0] = 1;
  // Process each connected component
  for (int i = 1; i <= n; i++) {
    if (!del[i]) {
      tmp.clear();
      memset(vis, 0, sizeof(vis));
      int s = dfs(i), m = tmp.size();
      // Check if component forms a valid structure for DP transition
      if ((m - 1) * m == s) {
        for (int j = n; j >= m - 1; j--)
          dp[j] = (dp[j] + dp[j - (m - 1)]) % mod;
        for (int j = 0; j < m; j++)
          del[tmp[j]] = 1;
      }
    }
  }
  long long ans = 0, fac = 1;
  // Combine results using factorial multiplication
  for (int i = n; i >= 0; i--) {
    ans = (ans + fac * dp[i] % mod) % mod;
    fac = fac * i % mod;
  }
  cout << ans << endl;
}
int main() { solve(); }


// https://github.com/VaHiX/CodeForces/