// Problem: CF 2021 E2 - Digital Village (Hard Version)
// https://codeforces.com/contest/2021/problem/E2

/*
 * E2. Digital Village (Hard Version)
 *
 * Purpose:
 * This program solves a dynamic connectivity and minimum spanning tree problem where we need to find
 * the minimum total latency for connecting houses requiring internet using k servers, for each k from 1 to n.
 * It uses Union-Find with path compression, a modified Kruskal's algorithm approach, and sorting optimizations.
 *
 * Techniques:
 * - Union-Find (Disjoint Set Union) with path compression
 * - Modified Kruskal’s algorithm for building MST
 * - Sorting and preprocessing to compute minimal costs efficiently
 * - Preprocessing result array based on sorted values
 *
 * Time Complexity: O(m log m + n^2)
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;
#define N 200000
int n, m, t, i, j, k, q, fa[N + 50];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
ll res[N + 50], f[N + 50], sz[N + 50];
vector<tuple<int, int, int>> v;
ll NMSL[N + 50], it;

// Function to merge two components with weighted edges
void hb(int x, int y, ll w) {
  ll t1, t2;
  // Cost of adding new node y into component x
  t1 = w * sz[x] - f[x];
  t2 = w * sz[y] - f[y];
  if (t1 < t2) {
    swap(x, y);
    swap(t1, t2);
  }
  if (sz[x] && sz[y])
    NMSL[++it] = t2; // Store minimal cost for merging
  fa[y] = x;
  sz[x] += sz[y];
  f[x] += w * sz[y];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n >> m >> q;
    it = 0;
    for (i = 1; i <= n; i++) {
      fa[i] = i;
      res[i] = f[i] = sz[i] = 0;
    }
    for (i = 1; i <= q; i++) {
      cin >> k;
      sz[k] = 1; // Mark nodes requiring internet
    }
    v = {};
    while (m--) {
      cin >> i >> j >> k;
      v.push_back({k, i, j}); // Store edge with weight and endpoints
    }
    sort(v.begin(), v.end()); // Sort edges by weight for Kruskal’s algorithm

    for (auto [w, x, y] : v) {
      x = find(x);
      y = find(y);
      if (x != y)
        hb(x, y, w); // Merge components
    }

    sort(NMSL + 1, NMSL + it + 1); // Sort the collected merge costs

    // Compute prefix sums for res array
    for (i = q - 1; i >= 1; i--)
      res[i] = res[i + 1] + NMSL[q - i];

    for (i = 1; i <= n; i++)
      cout << res[i] << ' ';
    cout << '\n';
  }
}


// https://github.com/VaHiX/codeForces/