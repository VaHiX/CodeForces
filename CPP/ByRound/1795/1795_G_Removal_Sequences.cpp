// Problem: CF 1795 G - Removal Sequences
// https://codeforces.com/contest/1795/problem/G

/*
Algorithm/Techniques: Topological sorting with bitset optimization for dependency tracking.
Time Complexity: O(N * M / 64 + N^2) where N is number of vertices and M is number of edges.
Space Complexity: O(N + M) for graph storage and auxiliary arrays.

This code solves the problem of counting "nice pairs" in a removal sequence of a graph.
A nice pair (x,y) means there exist two valid removal sequences where x is removed before y in one,
and y is removed before x in another.

The algorithm works as follows:
1. Build the graph and compute initial degrees.
2. Identify all initially unlocked vertices (degree == required degree).
3. Perform a topological-like traversal to generate dependency information about when each vertex becomes unlocked.
4. Use bitsets to efficiently track which vertices can be removed before others.
5. Calculate the final count of nice pairs based on mutual dependencies.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#pragma GCC target("popcnt")
using namespace std;
using ll = long long;
using ull = unsigned long long;
int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  vector<ull> dp(100'063 / 64);  // Bitset for tracking dependencies
  vector<int> graph[100'000];    // Adjacency list representation of graph
  int A[100'000];               // Degree requirements for each vertex
  vector<char> unlocked;        // Tracks whether a vertex is unlocked
  queue<int> q;                 // Queue for BFS-like process
  int deg[100'000];             // Current degree of each vertex
  vector<pair<int, int>> vals;  // Stores dependencies (from, to)
  while (T--) {
    int N, M;
    cin >> N >> M;
    vals.clear();
    for (int i = 0; i < N; i++)
      graph[i].clear();
    for (int i = 0; i < N; i++)
      cin >> A[i];
    while (M--) {
      int a, b;
      cin >> a >> b;
      a--;
      b--;
      graph[a].push_back(b);
      graph[b].push_back(a);
    }
    unlocked.assign(N, 0);
    for (int i = 0; i < N; i++)
      deg[i] = graph[i].size();
    for (int i = 0; i < N; i++) {
      if (deg[i] == A[i]) {
        unlocked[i] = true;
        q.push(i);
      }
    }
    while (q.size()) {
      int curr = q.front();
      q.pop();
      sort(graph[curr].begin(), graph[curr].end());
      for (int x : graph[curr]) {
        if (unlocked[x])
          continue;
        vals.push_back({curr, x});   // Record dependency
        deg[x]--;
        if (deg[x] == A[x]) {
          unlocked[x] = true;
          q.push(x);
        }
      }
    }
    ll ans = N * (ll)(N + 1) / 2;  // Total possible pairs
    for (int block = 0; block - 64 < N; block += 64) {
      dp.assign(N, 0ULL);  // Reset dp for current block
      const int end = min(block + 64, N);
      for (int i = block; i < end; i++)
        dp[i] = 1ULL << (i % 64);  // Initialize each set to itself
      for (auto [curr, x] : vals)
        dp[x] |= dp[curr];  // Propagate unlocks
      for (int i = 0; i < N; i++)
        ans -= __builtin_popcountll(dp[i]);  // Count bits set (dependencies)
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/