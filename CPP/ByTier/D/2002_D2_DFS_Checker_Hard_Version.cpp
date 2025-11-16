// Problem: CF 2002 D2 - DFS Checker (Hard Version)
// https://codeforces.com/contest/2002/problem/D2

/*
 * Problem: D2. DFS Checker (Hard Version)
 * 
 * Purpose: This program determines whether a given permutation of vertices 
 *          can represent a valid Depth-First Search (DFS) traversal of a 
 *          rooted tree. The DFS traversal is performed with an arbitrary 
 *          ordering of children, so the order of children at each node may vary.
 * 
 * Approach:
 * - Build the tree from parent information
 * - Compute DFS timing (in-time and out-time) for each node using dfs
 * - Maintain a bitmask to track which edges between adjacent elements in the 
 *   permutation are valid (i.e., they correspond to parent-child relationships)
 * - When swapping elements, update the validity of adjacent edges
 * - Output "YES" if (n - 1) edges are valid, otherwise "NO"
 * 
 * Time Complexity: O(n + q) for each test case (due to amortized analysis of updates)
 * Space Complexity: O(n) for storing tree, DFS times, and auxiliary arrays
 * 
 * Algorithms/Techniques: 
 * - DFS traversal with in-time and out-time
 * - Bitmask tracking of valid edges
 * - Persistent updates for swaps
 */

#include <bitset>
#include <iostream>
#include <string>
#include <utility>

using namespace std;
constexpr int _n = 3e5 + 7;
basic_string<int> v[_n]; // Adjacency list representation of tree
bitset<_n> B; // Bitmask to track valid edges
int t, n, q, cnt, a[_n], l[_n], r[_n], fa[_n], tot; // l[] = in-time, r[] = out-time

// DFS traversal to assign in-time and out-time to each node
void dfs(int x) {
  l[x] = ++cnt;
  for (int i : v[x])
    dfs(i);
  r[x] = cnt;
}

// Update the validity of the edge between a[x] and a[x+1]
void upd(int x) {
  // Check if a[x] and a[x+1] are in a valid parent-child relationship
  if (l[fa[a[x + 1]]] <= l[a[x]] && l[a[x]] <= r[fa[a[x + 1]]])
    tot += B[x] ^ 1, B[x] = 1; // Mark as valid
  else
    tot -= B[x] ^ 0, B[x] = 0; // Mark as invalid
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    B.reset(), tot = 0; // Reset bitmask and counter
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      v[i].clear(); // Clear adjacency list
    for (int i = 2; i <= n; ++i)
      cin >> fa[i], v[fa[i]] += i; // Build tree from parent info
    for (int i = 1; i <= n; ++i)
      cin >> a[i]; // Read permutation
    dfs(1); // Assign in-time and out-time
    for (int i = 1; i < n; ++i)
      upd(i); // Initialize the validity of all edges
    for (int x, y; q--;) {
      cin >> x >> y, swap(a[x], a[y]); // Swap elements in permutation
      if (x > 1)
        upd(x - 1); // Update validity of edge left of x
      if (x < n)
        upd(x); // Update validity of edge right of x
      if (y > 1)
        upd(y - 1); // Update validity of edge left of y
      if (y < n)
        upd(y); // Update validity of edge right of y
      cout << (tot == n - 1 ? "YES\n" : "NO\n"); // Check if all edges are valid
    }
  }
}


// https://github.com/VaHiX/CodeForces/