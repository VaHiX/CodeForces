// Problem: CF 1737 D - Ela and the Wiring Wizard
// https://codeforces.com/contest/1737/problem/D

/*
 * Problem: Ela and the Wiring Wizard
 * 
 * Approach:
 * - This problem involves finding the minimum time to send a package from machine 1 to machine n
 *   in a graph, where we can perform rewiring operations on edges to potentially reduce the
 *   shortest path.
 * - The core idea is to use Floyd-Warshall to precompute all-pairs shortest distances.
 * - Then, for each edge, we consider the effect of rewiring it by:
 *   1. Removing the edge and connecting one endpoint to another machine connected to the other endpoint.
 *   2. Calculating possible new paths from 1 to n using the rewired edge.
 * - We compute the minimum time considering all such rewiring possibilities.
 * 
 * Time Complexity: O(n^3 + m * n) where n^3 is from Floyd-Warshall and m*n from checking all edges
 * Space Complexity: O(n^2 + m) for storing distances and edge information
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
long long ans, w[300001];   // ans stores the result, w stores weights of edges
int n, m, _, i, j, k, a, b, x[300001], y[300001], dis[501][501]; // dis is the adjacency matrix for shortest paths

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> _;
  while (_--) {
    cin >> n >> m;
    ans = 1e18;   // Initialize answer to a large value
    memset(dis, 63, sizeof dis);  // Initialize distance matrix with large values (63 = 0x3f = 1061109567)
    for (i = 1; i <= n; i++)
      dis[i][i] = 0;   // Distance from a node to itself is 0
    
    // Read edges and initialize adjacency matrix
    for (i = 1; i <= m; i++)
      cin >> x[i] >> y[i] >> w[i], dis[x[i]][y[i]] = dis[y[i]][x[i]] = 1;
    
    // Floyd-Warshall to compute all-pairs shortest paths
    for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
        for (k = 1; k <= n; k++)
          dis[j][k] = min(dis[j][k], dis[j][i] + dis[i][k]);
    
    // For each edge, try rewiring it and calculate minimum path time
    for (i = 1; i <= m; i++) {
      // First check the current orientation (x[i] connected to y[i])
      for (j = 1; j <= n; j++)
        ans = min(ans, w[i] * min(dis[1][x[i]] + dis[y[i]][n] + 1,
                                  dis[1][j] + dis[j][n] + dis[x[i]][j] + 2));
      
      // Try both orientations of the edge by swapping x[i] and y[i]
      swap(x[i], y[i]);
      
      // After swap, now x[i] is connected to y[i] in the new orientation
      for (j = 1; j <= n; j++)
        ans = min(ans, w[i] * min(dis[1][x[i]] + dis[y[i]][n] + 1,
                                  dis[1][j] + dis[j][n] + dis[x[i]][j] + 2));
    }
    cout << ans << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/