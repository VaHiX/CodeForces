// Problem: CF 2006 B - Iris and the Tree
// https://codeforces.com/contest/2006/problem/B

/*
B. Iris and the Tree

Algorithms/Techniques:
- Tree traversal and depth calculation
- DFS numbering of nodes
- Difference array technique for range updates
- Prefix sum computation for efficient query processing

Time Complexity: O(n) per test case, where n is the number of vertices.
Space Complexity: O(n), for storing tree information and auxiliary arrays.

*/

#include <iostream>

#define int long long
using namespace std;
const int N = 2e5 + 9;
int n, W, fa[N], dep[N], siz[N];
int dist[N];

void solve() {
  cin >> n >> W; // Read number of nodes and total weight sum
  for (int i = 1; i <= n; i++)
    siz[i] = 1; // Initialize subtree sizes to 1
  for (int i = 2; i <= n; i++)
    cin >> fa[i], dep[i] = dep[fa[i]] + 1; // Compute depths and parents
  for (int i = n; i > 1; i--)
    siz[fa[i]] += siz[i]; // Calculate subtree sizes from bottom up
  dist[n] = dep[n]; // Initialize distance array with the deepest node's depth
  for (int i = 1; i < n; i++)
    dist[i] = dep[i] + dep[i + 1] - 2 * dep[fa[i + 1]]; // Precompute distances between consecutive nodes in DFS order
  int s = 0, cnt = n;
  for (int i = 1; i < n; i++) {
    int x, w;
    cin >> x >> w;
    s += w; // Accumulate known weights
    dist[x - 1]--; // Decrement distance at start of affected subtree
    if (dist[x - 1] == 0)
      cnt--; // Decrease count of active vertices if zero
    dist[x + siz[x] - 1]--; // Decrement distance at end of subtree
    if (dist[x + siz[x] - 1] == 0)
      cnt--; // Decrease count of active vertices if zero
    cout << s * 2 + (W - s) * cnt << " "; // Output the sum of maximum possible distances
  }
  cout << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/