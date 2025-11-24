// Problem: CF 2057 E1 - Another Exercise on Graphs (Easy Version)
// https://codeforces.com/contest/2057/problem/E1

/*
Algorithm: 
- This solution uses a combination of Minimum Spanning Tree (MST) and binary search on the answer.
- The key idea is to sort edges by weight and build a sequence of graphs where each graph includes more edges from the MST.
- For each query, binary search on the sorted edge weights to find the smallest k-th maximum edge weight for a path.

Time Complexity: O(m^2 * n + q * n * log(m))
Space Complexity: O(n^2 + m)

The algorithm works as follows:
1. Initially, construct a graph with all edges having weight 1 to compute shortest paths.
2. Sort edges in non-decreasing order of weight.
3. Build a sequence of graphs by adding edges from MST in order of increasing weight.
4. For each query, perform binary search on the edge weights to determine the minimum k-th maximum edge weight required for the path.
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <tuple>

using namespace std;
const int N = 404, oo = 1e9 + 7;
int n, m, q;
int par[N];
int findp(int u) { return u ^ par[u] ? par[u] = findp(par[u]) : u; }
bool united(int u, int v) { return findp(u) == findp(v); }
void unite(int u, int v) {
  u = findp(u), v = findp(v);
  if (u ^ v)
    par[v] = u;
}
array<int, 3> e[N * N / 2]; // Store edges as {weight, u, v}
int d[N][N][N]; // d[c][i][j] represents the shortest path between i and j using first c edges from MST
int res[N]; // Store the weights of edges added to MST in order
void solve(void) {
  cin >> n >> m >> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      d[0][i][j] = i == j ? 0 : oo; // Initialize distance matrix
    }
  }
  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    e[i] = {w, u, v};
    d[0][u][v] = d[0][v][u] = 1; // Initially all edges in graph have weight 1
  }
  // Floyd-Warshall to get initial shortest paths
  for (int k = 1; k <= n; k++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        d[0][u][v] = min(d[0][u][v], d[0][u][k] + d[0][k][v]);
      }
    }
  }
  sort(e + 1, e + 1 + m); // Sort edges by weight
  iota(par + 1, par + 1 + n, 1); // Initialize Union-Find structure
  int c = 0;
  for (int p = 1; p <= m; p++) {
    int u, v;
    tie(u, v) = {e[p][1], e[p][2]};
    if (!united(u, v)) { // If edge connects two different components
      unite(u, v);
      // Update the distance matrix using the newly added edge
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          d[c + 1][i][j] = min(
              {d[c][i][j], d[c][i][u] + d[c][v][j], d[c][i][v] + d[c][u][j]});
        }
      }
      res[++c] = e[p][0]; // Store edge weight
    }
  }
  while (q--) {
    int a, b, k;
    cin >> a >> b >> k;
    int ans = 0, l = 1, r = n - 1, mid;
    while (l <= r) {
      mid = (l + r) >> 1;
      // If path with at least k edges exists in current graph, decrease r and store answer
      if (d[mid][a][b] < k) {
        ans = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    cout << res[ans] << ' '; // Output the required edge weight
  }
  cout << '\n';
}
signed main(void) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/