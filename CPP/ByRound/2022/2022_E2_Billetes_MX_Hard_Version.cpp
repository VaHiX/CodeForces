// Problem: CF 2022 E2 - Billetes MX (Hard Version)
// https://codeforces.com/contest/2022/problem/E2

/*
 * Problem: E2. Billetes MX (Hard Version)
 *
 * Purpose:
 *   This code solves a problem involving assigning values to a grid such that
 *   all subgrids satisfy a XOR constraint on their corners. It uses Union-Find
 *   with path compression and value tracking to manage connected components and
 *   validate XOR constraints. After each query, it updates the component count
 *   and returns the number of valid assignments based on the remaining free
 *   variables, calculated as 2^(number of connected components - fixed cells).
 *
 * Algorithms:
 *   - Union-Find (Disjoint Set Union) with path compression and value tracking
 *   - XOR constraint propagation in a 2D grid using coordinate mapping
 *
 * Time Complexity:
 *   O((n + m + k + q) * α(n + m)) where α is the inverse Ackermann function.
 *   Each DSU operation (union/find) takes nearly constant time.
 *
 * Space Complexity:
 *   O(n + m) for the DSU structures and arrays.
 */

#include <iostream>
#include <utility>
using namespace std;

const int N = 2e5 + 5, M = 1e9 + 7;
int t, n, m, k, q, p[N], x, y, z, dsu[N], sz[N], val[N], ok, cmps;

// Merge two sets with XOR constraint c (x ^ y = c)
void mrg(int a, int b, int c) {
  // Traverse to root while propagating XOR values
  while (a != dsu[a])
    c ^= val[a], a = dsu[a];
  while (b != dsu[b])
    c ^= val[b], b = dsu[b];

  // If already in same component, check XOR consistency
  if (a == b) {
    if (c)
      ok = 0;  // Inconsistent constraint
    return;
  }

  // Union by size: make sure 'a' is smaller
  if (sz[a] > sz[b])
    swap(a, b);

  // Merge a into b and update val and size
  dsu[a] = b, sz[b] += sz[a], val[a] = c, cmps--;
}

int main() {
  ios::sync_with_stdio(0), cout.tie(0), cin.tie(0);
  
  // Precompute powers of 2^30 mod M for fast calculation
  for (p[0] = x = 1; x < N; x++)
    p[x] = p[x - 1] * (1LL << 30) % M;

  cin >> t;
  while (t--) {
    cin >> n >> m >> k >> q;
    
    ok = 1, cmps = n + m - 1;  // Initially, there are n+m-1 independent components
    
    // Initialize DSU structures
    for (x = 1; x <= n + m; x++)
      dsu[x] = x, sz[x] = 1, val[x] = 0;

    // Process fixed cells and build constraints
    while (k--)
      cin >> x >> y >> z, mrg(x, y + n, z);  // Map column to n+y to distinguish rows from columns

    cout << ok * p[cmps] << "\n";

    // Process queries and output results after each update
    while (q--) {
      cin >> x >> y >> z, mrg(x, y + n, z), cout << ok * p[cmps] << "\n";
    }
  }
}


// https://github.com/VaHiX/codeForces/