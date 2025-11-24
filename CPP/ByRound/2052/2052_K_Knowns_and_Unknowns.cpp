// Problem: CF 2052 K - Knowns and Unknowns
// https://codeforces.com/contest/2052/problem/K

// Problem: Given two professors' ordered lists of students and their partial knowledge of which students visited today,
// determine for each student whether they definitely visited, definitely did not visit, or cannot be determined.
// Algorithm Used:
//   - Bipartite Matching with augmenting paths (Hopcroft-Karp style)
//   - Transitive closure via Floyd-Warshall logic on a constructed graph
// Time Complexity: O(n^3) per test case due to matching and transitive closure steps
// Space Complexity: O(n^2) for the adjacency matrix and auxiliary arrays

#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;
constexpr int N = 2e3;
int p[2][N], q[2][N], ng[2], bnd[2][N], gs[2][N], gn[2][N], vis[N], used[N];
vector<int> gm[2][N], mt[N];
bitset<2 * N> a[2 * N];
bool try_match(int v) {
  if (!vis[v]++) // Mark vertex as visited to avoid cycles in DFS
    for (auto x : gm[0][v]) // Iterate through neighbors in matching graph
      if (!used[x]) { // If neighbor is unmatched
        int u = gn[1][x]; // Get corresponding vertex in second partition
        if (mt[u].size() < gs[1][u]) // Check capacity constraint
          return mt[u].push_back(x), used[x] = 1; // Assign match, mark as used
        for (auto &xx : mt[u]) // Try to find augmenting path by pushing back
          if (try_match(gn[0][xx])) // Recursive try on alternate vertex
            return used[xx] = 0, xx = x, used[x] = 1; // Reassign and mark updated
      }
  return 0; // No match found for this path
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int tc;
  cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; mt[i].clear(), ++i)
      for (int c : {0, 1})
        gm[c][i].clear(); // Clear data structures for new case
    for (int i = 0; i < 2 * n; ++i)
      a[i].reset(); // Reset adjacency matrix
    ng[0] = ng[1] = 0;
    for (int c : {0, 1}) {
      for (int i = 0; i < n; ++i)
        cin >> p[c][i], q[c][--p[c][i]] = i; // Read and store permutation with offset
    }
    int k;
    cin >> k;
    int t = 2 * k;
    for (int c : {0, 1}) {
      int j = 0;
      for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        --t;
        if (~x) { // If element isn't -1, process it
          --x;
          if (bnd[c][ng[c]] + i - j > q[c][x]) // Check boundary condition
            goto fail;
          if (bnd[c][ng[c]] != q[c][x]) // Set up segments for matching constraints
            gs[c][ng[c]] = i - j, bnd[c][++ng[c]] = q[c][x];
          gs[c][ng[c]] = 1; 
          bnd[c][++ng[c]] = q[c][x] + 1;
          j = i + 1;
        }
      }
      if (bnd[c][ng[c]] < n) // Final segment boundary
        gs[c][ng[c]] = k - j, bnd[c][++ng[c]] = n;
      for (int i = 0, j = 0; i < n; ++i, j += i == bnd[c][j + 1]) // Build bipartite edges
        gm[c][j].push_back(p[c][i]), gn[c][p[c][i]] = j;
    }
    fill(used, used + n, 0); // Reset usage tracking
    int sz;
    for (int i = sz = 0; i < n; ++i)
      if (gs[0][gn[0][i]]-- > 0) { // Process vertices with valid match counts
        sz += try_match(gn[0][i]); // Attempt augmenting paths
        fill(vis, vis + n, 0); // Reset visited tracking
      }
    if (sz < k) {
    fail:; // Label for inconsistency
      while (t--)
        cin >> sz;
      cout << "Inconsistent\n";
      continue;
    }
    for (int x = 0; x < n; ++x)
      a[used[x] * n + gn[used[x]][x]][!used[x] * n + gn[!used[x]][x]] = 1; // Construct graph based on matchings
    for (int i = 0; i < 2 * n; ++i)
      for (int j = 0; j < 2 * n; ++j)
        if (a[j][i])
          a[j] |= a[i]; // Floyd-Warshall-like transitive closure
    for (int x = 0; x < n; ++x)
      cout << "Y?N"[a[gn[0][x]][n + gn[1][x]] + 1 - a[n + gn[1][x]][gn[0][x]]]; // Output determination results
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/