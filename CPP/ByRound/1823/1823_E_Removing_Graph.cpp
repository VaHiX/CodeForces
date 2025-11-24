// Problem: CF 1823 E - Removing Graph
// https://codeforces.com/contest/1823/problem/E

/*
 * Problem: E. Removing Graph
 * 
 * Purpose: Determine the winner of a game played on a graph where each vertex has degree 2.
 *          Players take turns removing connected subgraphs of size between l and r.
 *          The game is about the nim-sum of cycle lengths in the graph.
 *
 * Algorithm:
 * - Each connected component in the graph is a cycle since every vertex has degree 2.
 * - For each cycle of size s, we calculate its contribution to the nim-sum:
 *   - If s >= l + r, the cycle contributes 0 to the nim-sum.
 *   - Otherwise, the cycle contributes (s / l) to the nim-sum.
 * - If the total nim-sum is non-zero, Alice wins; otherwise, Bob wins.
 *
 * Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (n forDSU operations)
 * Space Complexity: O(n) for storing DSU structure
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
struct Dsu {
  vector<int> dsu_vt;
  vector<int> sz_vt;
  Dsu() { init(0); }
  Dsu(int size) { init(size); }
  void init(int size) {
    dsu_vt.resize(size + 1);
    sz_vt.resize(size + 1);
    for (int i = 0; i <= size; i++)
      dsu_vt[i] = i, sz_vt[i] = 1;
  }
  int find(int u) { return dsu_vt[u] ^ u ? dsu_vt[u] = find(dsu_vt[u]) : u; }
  int size(int u) { return sz_vt[find(u)]; }
  void merge(int u, int v) {
    int ru = find(u), rv = find(v);
    if (ru != rv) {
      if (ru < rv)
        swap(ru, rv);
      dsu_vt[ru] = rv;
      sz_vt[rv] += sz_vt[ru];
    }
  }
};
void solve(int n, int l, int r) {
  Dsu dsu(n);
  for (int i = 1, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    dsu.merge(u, v);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (dsu.find(i) == i)
      ans ^= (dsu.size(i) >= l + r ? 0 : dsu.size(i) / l); // Compute nim-sum
  printf("%s\n", ans > 0 ? "Alice" : "Bob");
}
int main() {
  int n, l, r;
  while (cin >> n >> l >> r)
    solve(n, l, r);
  return 0;
}


// https://github.com/VaHiX/CodeForces/