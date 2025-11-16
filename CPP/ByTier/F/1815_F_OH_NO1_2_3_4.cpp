// Problem: CF 1815 F - OH NO1 (-2-3-4)
// https://codeforces.com/contest/1815/problem/F

/*
 * Purpose: Solve a graph problem where we need to assign values to edges such that
 *          adjacent vertices have different weights after operations.
 *          Each edge is part of exactly one triangle, and each triangle has 3 edges.
 *          For each edge, we add an integer x (1-4) to both vertices of the edge.
 *          After all operations, no two adjacent vertices should have equal final weights.
 *
 * Algorithm: 
 * 1. Initially, assign fixed small values (3,1,1) to each triangle's edges.
 * 2. For each vertex, process its adjacent triangles in order.
 * 3. For each triangle, check if any vertex weight conflicts with existing weights.
 * 4. Adjust values for conflicting edges to resolve weight conflicts.
 * 5. Output the adjusted values for all edges of all triangles.
 *
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 */
#include <array>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
const long long mod = 998244353;
const int N = 2e6 + 1;
long long n, m;
vector<pair<int, int>> adj[N]; // adjacency list tracking which triangle connects to which vertex
array<int, 3> e[N];           // stores triangle edges: e[i] = [a, b, c]
array<int, 3> f[N];           // stores final edge values for triangle i
long long a[N], b[N];         // vertex weights (a[i] stores final weight of vertex i)
pair<int, int> vis[10000005]; // for tracking conflicting vertex weights

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    adj[i].clear();
  for (int i = 1; i <= n; i++)
    cin >> a[i]; // read initial weights
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> e[i][j]; // read triangle edges
      adj[e[i][j]].push_back({i, j}); // record triangle and edge index for each vertex
    }
    f[i][0] = 3; // initial assignment for triangle edges
    f[i][1] = 1;
    f[i][2] = 1;
    a[e[i][0]] += f[i][0] + f[i][2]; // update vertex weights based on triangle assignments
    a[e[i][1]] += f[i][1] + f[i][0];
    a[e[i][2]] += f[i][2] + f[i][1];
  }
  for (int i = 1; i <= n; i++) {
    // Mark current vertex's edge weights in the vis array to detect conflicts
    for (auto c : adj[i]) {
      for (int d = 0; d < c.second; d++) {
        vis[a[e[c.first][d]]] = {c.first, d}; // record which triangle and edge causes this weight
      }
    }
    // Resolve conflicts if any exist for the current vertex
    while (vis[a[i]].first != 0) {
      int ed = vis[a[i]].first; // get conflicting edge's triangle ID
      if (i == e[ed][1]) {
        // conflict happens at vertex (e[ed][1]), adjust values accordingly
        a[i]++;
        a[e[ed][2]]++; // update vertex weight
        f[ed][1]++;   // increment edge value
      } else {
        // adjust both vertices to avoid conflict
        a[i] += 2;
        f[ed][0]--;   // reduce one edge value
        f[ed][1]++;   // increase another
        f[ed][2]++;   // increase the third
      }
    }
    // Clear the vis array for next vertex
    for (auto c : adj[i]) {
      for (int d = 0; d < c.second; d++) {
        vis[a[e[c.first][d]]] = {0, 0};
      }
    }
  }
  // Output final edge assignments for all triangles
  for (int i = 1; i <= m; i++)
    cout << f[i][0] << ' ' << f[i][1] << ' ' << f[i][2] << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/