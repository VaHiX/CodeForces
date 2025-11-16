// Problem: CF 2000 G - Call During the Journey
// https://codeforces.com/contest/2000/problem/G

/*
Problem: G. Call During the Journey

Purpose:
This code solves a shortest path problem where we need to find the latest possible departure time from intersection 1 to reach intersection n on time, considering a phone call window during which bus travel is blocked but walking is allowed.
The solution uses a modified Dijkstra's algorithm with priority queue to compute maximum valid times.

Algorithms/Techniques:
- Modified Dijkstra's algorithm with a max priority queue
- Time-aware graph traversal with conditional edge relaxation

Time Complexity: O((V + E) * log V), where V = n (intersections), E = m (streets)
Space Complexity: O(V + E), for storing the graph and auxiliary arrays

*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#define $(x, i) std::get<i>(x)
std::vector<std::tuple<int, int, int>> v[100005]; // adjacency list: {to, bus_time, walk_time}
int dis[100005]; // maximum time to reach each node (initialized with negative values)
bool vis[100005]; // visited array for Dijkstra
int T, n, m, t0, t1, t2;

// Function that performs the modified Dijkstra algorithm
int bfs() {
  std::priority_queue<std::pair<int, int>> q; // max heap: {time, node}
  memset(dis + 1, 192, n << 2); // Initialize dis array with -192 * 4 = -768 (approx. INT_MIN)
  memset(vis + 1, 0, n); // Mark all nodes as unvisited
  q.emplace(dis[n] = t0, n); // Start from node n with time t0 (we go backwards in time)
  while (!q.empty()) {
    int x = q.top().second; // Current node
    q.pop();
    if (vis[x]) continue; // Skip already visited nodes
    vis[x] = true;
    for (const auto &i : v[x]) { // For all neighbors of x
      static int val; // Temporary variable to store new time
      // If we're outside the phone call window or can go through,
      // then we are allowed to take bus, else adjust accordingly
      if (dis[x] - $(i, 1) >= t2 || dis[x] <= t1)
        val = dis[x] - $(i, 1); // Go by bus
      else
        val = std::max(dis[x] - $(i, 2), t1 - $(i, 1)); // Stay within phone call window
      if (dis[$(i, 0)] < val) // Relax edge if better time found
        q.emplace(dis[$(i, 0)] = val, $(i, 0));
    }
  }
  return std::max(dis[1], -1); // Return max time to reach node 1 (or -1 if impossible)
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d", &n, &m, &t0, &t1, &t2);
    for (int i = 1; i <= n; ++i)
      v[i].clear(); // Clear graph edges
    for (int x, y, z1, z2; m--;)
      scanf("%d%d%d%d", &x, &y, &z1, &z2), v[x].emplace_back(y, z1, z2),
          v[y].emplace_back(x, z1, z2); // Add bidirectional edges
    printf("%d\n", bfs()); // Output result for this case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/