// Problem: CF 1938 J - There and Back Again
// https://codeforces.com/contest/1938/problem/J

/*
There and Back Again
Input file: standard input
Output file: standard output
Time limit: 3 seconds
Memory limit: 1024 megabytes

Problem description:
We are given a bidirectional graph with n cities and m roads. Each road has a travel time.
We must find the minimum total traversal time to go from city 1 to city n, and then return to city 1,
such that the sets of roads used in both journeys are different.

Algorithms/Techniques:
- Dijkstra's algorithm for finding shortest path from city 1 to all other cities
- BFS-like reconstruction of one path using parent array
- Iteration over edges to find minimum alternative path with different roads
- Bit manipulation trick (XOR) to alternate between endpoints of an edge

Time Complexity: O((V + E) * log V) where V = n, E = m for Dijkstra's algorithm
Space Complexity: O(V + E) for adjacency list, distance array, parent array and edge storage

*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int INF = 2e8;
struct edge {
  int a, b, c;
  edge(int a, int b, int c) : a(a), b(b), c(c) {}
};
int n, m;
vector<edge> adj[101010]; // Adjacency list for graph
bool vst[303030];         // Visited array to track which edges are used in forward path
int dst[101010];          // Distance array for shortest distances from node 1
int par[101010];          // Parent array to reconstruct path
int e[303030][4];         // Edge information storage [u, v, time, index]
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    auto &[u, v, t, idx] = e[i];
    cin >> u >> v >> t;
    idx = i;
    adj[u].emplace_back(v, t, i);
    adj[v].emplace_back(u, t, i);
  }
  for (int i = 2; i <= n; ++i) {
    dst[i] = INF;
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push(pair<int, int>(0, 1));
  while (!pq.empty()) {
    auto [d, cur] = pq.top();
    pq.pop();
    if (dst[cur] != d) // Skip outdated entries in priority queue
      continue;
    for (auto [nxt, t, i] : adj[cur]) {
      if (dst[nxt] > d + t) {
        dst[nxt] = d + t;
        pq.push(pair<int, int>(d + t, nxt));
        par[nxt] = i; // Store the edge that improved distance to nxt
      }
    }
  }
  if (dst[n] == INF) {
    cout << -1;
    return 0;
  }
  // Mark edges on the shortest path from 1 to n as used
  for (int cur = n; cur != 1;) {
    auto [u, v, t, i] = e[par[cur]];
    vst[i] = 1;
    cur ^= u ^ v; // XOR to move to other endpoint of edge
  }
  e[0][0] = 1;    // Dummy node to help with traversal logic
  int ans = INF;
  for (int cur = n; cur != 0;) {
    for (auto [nxt, t, i] : adj[cur]) {
      if (vst[i])
        continue; // Skip edges that are part of forward path
      ans = min(ans, dst[n] + 2 * t); // Path going back via one edge
      ans = min(ans, dst[n] - dst[cur] + t + dst[nxt]); // Two paths merge at some point
    }
    auto [u, v, t, i] = e[par[cur]];
    cur ^= u ^ v; // Move to previous node in path
  }
  if (ans == INF)
    cout << -1;
  else
    cout << dst[n] + ans;
}


// https://github.com/VaHiX/codeForces/