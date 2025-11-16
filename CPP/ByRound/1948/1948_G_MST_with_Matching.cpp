// Problem: CF 1948 G - MST with Matching
// https://codeforces.com/contest/1948/problem/G

#pragma GCC optimize("Ofast")
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
// Flowerbox: 
// Purpose: Find the minimum cost spanning tree in a graph where the cost includes
// both the sum of edge weights and c times the maximum matching in the tree.
// Algorithm: 
// - Use Kruskal's algorithm with Union-Find to build spanning trees
// - Try all possible subsets of vertices (up to 2^n) to form a maximum matching
// - For each subset, build a spanning tree to minimize cost using greedy approach
// Time Complexity: O(2^n * n^2 * α(n)) where α(n) is inverse Ackermann function
// Space Complexity: O(n^2) for storing edges and parent array

struct RR {
  int a;
  int b;
  int cost;
  RR(int i, int j) : a(i), b(j) {}
};
bool operator<(const RR &c, const RR &d) {
  if (c.cost < d.cost)
    return 1;
  if (c.cost > d.cost)
    return 0;
  if (c.a < d.a)
    return 1;
  if (c.a > d.a)
    return 0;
  return c.b < d.b;
}
vector<RR> edges;
vector<int> parent;
int n;
int chunk(int a) {
  int u = a;
  while (parent[u] >= 0)
    u = parent[u];
  return u;
}
void reset(int a, int p) {
  int u = a;
  while (parent[u] >= 0) {
    int v = parent[u];
    parent[u] = p;
    u = v;
  }
}
void try_(int &ans, int mask, int tot) {
  fill(parent.begin(), parent.end(), -1);
  int n_edges = 0;
  for (const auto &[a, b, cost] : edges) {
    // Skip edges that connect vertices outside the current subset
    if (((1 << a) & mask) == 0 && ((1 << b) & mask) == 0)
      continue;
    int u = chunk(a);
    int v = chunk(b);
    if (u == v)
      continue;
    // Union operation with path compression
    if (parent[u] > parent[v]) {
      reset(a, v);
      reset(b, v);
      parent[v] += parent[u];
      parent[u] = v;
    } else {
      reset(a, u);
      reset(b, u);
      parent[u] += parent[v];
      parent[v] = u;
    }
    // Early termination if cost exceeds current answer
    if ((tot += cost) >= ans)
      return;
    if (++n_edges == n - 1) {
      ans = tot;
      return;
    }
  }
}
int main() {
  cin.tie(NULL);
  ios::sync_with_stdio(false);
  int c;
  cin >> n >> c;
  assert(n >= 1 && n <= 20 && c >= 0 && c <= 1000000);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      RR r(i, j);
      cin >> r.cost;
      assert(r.cost >= 0 && r.cost <= 1000000);
      if (r.cost == 0)
        continue;
      if (i < j)
        edges.push_back(r);
    }
  if (n == 1) {
    cout << "0\n";
    return 0;
  }
  parent.assign(n, -1);
  sort(edges.begin(), edges.end());
  int rv = 40000000;
  // Try all subsets of vertices to consider potential matchings
  for (int mask = 1; mask < (1 << n); mask++) {
    int b = __builtin_popcount(mask);
    if (b < n / 2)
      try_(rv, mask, b * c);
  }
  try_(rv, (1 << n) - 1, (n / 2) * c);
  cout << rv << '\n';
}


// https://github.com/VaHiX/CodeForces/