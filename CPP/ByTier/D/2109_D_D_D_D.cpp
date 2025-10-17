// Problem: CF 2109 D - D/D/D
// https://codeforces.com/contest/2109/problem/D

/*
D. D/D/D

Problem Description:
Given a simple, connected, undirected graph with n vertices and m edges, and a multiset A of ℓ elements,
we start at vertex 1 and can traverse walks of length k (where k is an element from A) to reach other vertices.
We aim to determine whether each vertex i (1 ≤ i ≤ n) is reachable using the original multiset A.

Key Techniques:
- BFS traversal for computing distances from node 1
- Dynamic programming on parity to track max distance achievable by even/odd step counts
- Preprocessing all possible moves based on elements in A and applying BFS

Time Complexity: O(n + m + ℓ * log(max(A)))
Space Complexity: O(n + m + ℓ)

Algorithms:
- BFS for shortest path in graph
- Dynamic Programming with parity optimization
*/

#include <limits.h>
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

typedef long long ll;
using namespace std;

void solve() {
  int n, m, l;
  cin >> n >> m >> l;
  vector<int> a(l), dis[2]; // dis[0] and dis[1] store distances for even/odd steps
  for (auto &i : a)
    cin >> i;

  // Initialize distance array with INT_MAX for all vertices, excepting vertex 1
  dis[0] = vector<int>(n + 1, INT_MAX);
  dis[1] = dis[0];

  vector<vector<int>> adj(n + 1); // adjacency list representation of graph
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Compute max possible distance for even and odd steps from initial position
  int msum[2] = {0, 0};
  for (auto k : a) {
    int l = msum[0] + k;
    int r = msum[1] + k;
    msum[l % 2] = max(msum[l % 2], l);
    msum[r % 2] = max(msum[r % 2], r);
  }

  // BFS setup - start from vertex 1 with distance 0
  dis[0][1] = 0;
  vector<int> cq{1}; // current queue

  // BFS traversal to compute distances for each node, grouped by parity of steps
  for (int i = 1; cq.size(); ++i) {
    vector<int> nq; // next queue
    int j = i % 2; // parity of current step count
    for (auto u : cq) {
      for (auto nxt : adj[u]) {
        if (dis[j][nxt] != INT_MAX)
          continue; // skip if already visited with same parity
        dis[j][nxt] = i; // mark distance and add to next queue
        nq.push_back(nxt);
      }
    }
    cq = nq;
  }

  // Check for each vertex whether it's reachable within max allowed steps of given parity
  for (int i = 1; i <= n; ++i) {
    int good = 0;
    for (int p = 0; p <= 1; ++p) {
      if (dis[p][i] <= msum[p]) {
        good = 1;
      }
    }
    cout << good;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/