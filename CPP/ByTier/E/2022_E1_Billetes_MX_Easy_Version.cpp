// Problem: CF 2022 E1 - Billetes MX (Easy Version)
// https://codeforces.com/contest/2022/problem/E1

/*
 * Problem: E1. Billetes MX (Easy Version)
 * 
 * This problem involves assigning integers to cells in an n x m grid such that
 * all subgrids have XOR of corner values equal to 0. The grid has k fixed cells
 * and q updates (in this version, q=0). We want to count how many ways to complete
 * the grid such that it's "beautiful".
 *
 * Approach:
 * - Model the constraints as a union-find data structure with path compression
 *   and tracking of XOR differences between connected components.
 * - Each cell (r, c) is mapped to node r in union-find (row nodes) or n + c (column nodes).
 * - When linking two nodes, we store their XOR difference in _dist array.
 * - If inconsistency arises during linking (e.g., existing constraint contradicts current),
 *   return 0 as no valid assignment exists.
 * - After all links:
 *     - Count connected components (cc)
 *     - The number of free variables = cc - 1
 *     - Result = 2^(freeCount) mod M
 *
 * Time Complexity: O(k log(n+m) + q log(n+m))
 * Space Complexity: O(n + m)
 */

#include <iostream>
#include <stdio.h>
#include <utility>
using namespace std;
#define nl '\n'
#define endl ? ?
using ll = long long;
using PII = pair<int, int>;
const int N = 1e5 + 10, M = 1000000007;

// Fast exponentiation to compute (2^freeCount) mod M
int getans(int freeCount) {
  if (freeCount < 0)
    return 0;
  ll res = 1, p2 = 1 << 30; // p2 represents 2^30, used for modular exponentiation
  while (freeCount) {
    if (freeCount & 1)
      res = res * p2 % M;
    p2 = p2 * p2 % M;
    freeCount >>= 1;
  }
  return res;
}

int n, m, k, q;

struct {
  int f[N * 2], size[N * 2], _dist[N * 2], cc; // Union-find related arrays

  void init() {
    cc = n + m;
    for (int i = 1; i <= n + m; ++i) {
      f[i] = i, size[i] = 1;
      _dist[i] = 0;
    }
  }

  int find(int x) {
    if (f[x] == x)
      return x;
    return find(f[x]); // Find root with path compression
  }

  int xdist(int x) {
    if (f[x] == x)
      return 0;
    return _dist[x] ^ xdist(f[x]); // Return XOR distance from node to root
  }

  bool link(int u, int v, int w) {
    int fu = find(u), fv = find(v);
    if (fu == fv)
      return (xdist(u) ^ xdist(v)) == w; // Check consistency

    if (size[fu] < size[fv])
      swap(fu, fv), swap(u, v); // Union by size to keep tree balanced

    _dist[fv] = xdist(u) ^ xdist(v) ^ w; // Set XOR difference based on existing values
    f[fv] = fu;
    size[fu] += size[fv];
    cc--;
    return true;
  }
} dsu;

void solve() {
  cin >> n >> m >> k >> q;
  dsu.init();
  bool flag = 1;
  for (int i = 0, r, c, v; i < k; ++i) {
    cin >> r >> c >> v;
    if (flag)
      flag = dsu.link(r, n + c, v); // Link row and column node with their XOR value
  }

  if (!flag)
    cout << 0 << nl; // Inconsistent constraints
  else
    cout << getans(dsu.cc - 1) << nl; // Compute valid configurations

  for (int i = 0, r, c, v; i < q; ++i) {
    cin >> r >> c >> v;
    if (flag)
      flag = dsu.link(r, n + c, v); // Process update
    if (flag)
      cout << getans(dsu.cc - 1) << nl;
    else
      cout << 0 << nl;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T = 1;
  cin >> T;
  while (T--) {
    solve();
  }
  fflush(stdout);
}


// https://github.com/VaHiX/codeForces/