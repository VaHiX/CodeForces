// Problem: CF 2057 E2 - Another Exercise on Graphs (hard version)
// https://codeforces.com/contest/2057/problem/E2

/*
 * Problem: E2. Another Exercise on Graphs (hard version)
 * 
 * Purpose:
 *   This code solves a problem where we are given a connected weighted undirected graph
 *   and need to answer queries about the k-th maximum edge weight among all paths
 *   from node a to node b.
 *   
 *   Key Techniques:
 *   - Floyd-Warshall for initial shortest paths
 *   - Sorting edges by weight in ascending order
 *   - Binary search on the answer with dynamic updates of distances
 *   
 *   Approach:
 *   - Initially compute all-pairs shortest distances using Floyd-Warshall
 *   - Iterate through edges in ascending order of weights, for each edge:
 *     - If the edge is part of some path (not redundant), add its weight to dst array
 *     - Update the distance matrix with this edge considered
 *   - For each query, binary search on the array of weights to find the minimum
 *     weight such that there exists a path with all edges having weights greater than or equal to it,
 *     and the path length is at most k (or the path exists with k edges).
 *   
 *   Time Complexity: O(m^2 * n + q * log m)
 *   Space Complexity: O(n^2 + m)
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 405;
struct dat {
  int u, v, w;
} e[N * N];
int dis[N][N][N], dst[N];
void ATRI() {
  int n, m, q;
  cin >> n >> m >> q;
  // Initialize the distance matrix with large values
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dis[0][i][j] = i == j ? 0 : 1e9;
  // Read edges and initialize direct distances
  for (int i = 1, u, v, w; i <= m; ++i)
    cin >> u >> v >> w, e[i] = {u, v, w}, dis[0][u][v] = dis[0][v][u] = 1;
  // Floyd-Warshall to get initial distances (in terms of number of edges)
  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[0][i][j] = min(dis[0][i][j], dis[0][i][k] + dis[0][k][j]);
  // Sort edges by their weights in ascending order
  sort(e + 1, e + m + 1, [=](dat x, dat y) { return x.w < y.w; });
  int cnt = 0;
  // Process each edge in sorted order to build up the updated distance matrix
  for (int k = 1; k <= m; ++k) {
    auto [u, v, w] = e[k];
    // Skip if this edge doesn't contribute to a path (i.e., it was already included)
    if (!dis[cnt][u][v])
      continue;
    dst[++cnt] = w; // Store the edge weight
    // Update the distance matrix considering the edge addition
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        dis[cnt][i][j] = min(dis[cnt - 1][i][j],
                             min(dis[cnt - 1][i][u] + dis[cnt - 1][v][j],
                                 dis[cnt - 1][i][v] + dis[cnt - 1][u][j]));
  }
  // Process queries
  while (q--) {
    int u, v, x;
    cin >> u >> v >> x;
    int l = 1, r = cnt, mid, res = -1;
    // Binary search over the weight array to find the minimum weight threshold
    while (l <= r) {
      mid = l + r >> 1;
      // If path exists with current threshold, try to decrease threshold
      if (dis[mid][u][v] < x)
        res = mid, r = mid - 1;
      else
        l = mid + 1;
    }
    cout << dst[res] << " \n"[!q];
  }
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    ATRI();
  return 0;
}


// https://github.com/VaHiX/CodeForces/