// Problem: CF 1764 F - Doremy's Experimental Tree
// https://codeforces.com/contest/1764/problem/F

/*
Purpose: This program reconstructs a tree from given experimental values f(i,j) which represent the sum of shortest distances from all vertices to the cycle formed by adding an edge of weight 1 between vertices i and j.

Algorithms/Techniques:
- The core idea is to use the relationship between the distances in the original tree and the new distances after adding an edge of weight 1.
- The key mathematical insight is that for a tree with edge weights w_ij, we can compute the effective edge weights e[i][j] using the formula: 
    e[i][j] = (f[i][i] + f[j][j] - 2 * f[i][j]) / n
- The problem then reduces to computing a minimum spanning tree (MST) of the reconstructed edge weights using Prim's algorithm.
- Once all edges of the MST are determined, they are output in the expected format.

Time Complexity: O(n^2) - Prim's MST algorithm with a simple implementation using two nested loops.
Space Complexity: O(n^2) - Storage for the matrix of edge weights e, and auxiliary arrays like d, p, and vis.

*/
#include <string.h>
#include <iostream>

#define int long long
using namespace std;
int const N = 2010;
int n, a[N][N], e[N][N], d[N], p[N];
bool vis[N];
signed main() {
  ios::sync_with_stdio(0);
  cin >> n;
  // Read in the input values f(i,j)
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++)
      cin >> a[i][j];
  // Precompute the effective edge weights using the formula
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++)
      e[i][j] = e[j][i] = (a[i][i] + a[j][j] - a[i][j] * 2) / n;
  // Initialize distances for Prim's algorithm
  memset(d, 0x3f, sizeof d), d[1] = 0;
  for (int i = 1; i <= n; i++) {
    int t = 0;
    // Find the minimum distance vertex not yet included in MST
    for (int j = 1; j <= n; j++)
      if (!vis[j] && d[j] < d[t])
        t = j;
    vis[t] = 1;
    // Output the edge if not the first vertex
    if (i > 1)
      cout << p[t] << " " << t << " " << e[p[t]][t] << "\n";
    // Update distances of adjacent vertices
    for (int j = 1; j <= n; j++)
      if (!vis[j] && d[j] > e[t][j])
        p[j] = t, d[j] = e[t][j];
  }
}


// https://github.com/VaHiX/CodeForces/