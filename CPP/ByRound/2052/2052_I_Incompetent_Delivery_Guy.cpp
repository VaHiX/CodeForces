// Problem: CF 2052 I - Incompetent Delivery Guy
// https://codeforces.com/contest/2052/problem/I

/*
 * Problem: Incompetent Delivery Guy
 * 
 * Purpose:
 *   Given a directed weighted graph representing towers and passages in Isengard,
 *   determine the maximum incompetence level d such that an orc with incompetence d
 *   can successfully deliver a present from entrance tower (1) to Orthanc (n),
 *   following only passages marked with flashing signs that lie on shortest paths.
 *
 * Algorithms/Techniques:
 *   - Dijkstra's algorithm to compute shortest distances from Orthanc (n)
 *   - Topological sorting via Kahn's algorithm for processing nodes
 *   - BFS-style traversal to compute maximum number of "hanging around" choices
 *     while maintaining shortest path constraints
 * 
 * Time Complexity: O(m * log n + n + m) where m is the number of edges and n is number of vertices.
 * Space Complexity: O(n + m)
 */

#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  // Build adjacency list for reverse graph (from destination to source)
  std::vector<std::vector<std::array<int, 2>>> adj(n);
  for (int i = 0; i < m; i++) {
    int u, v, t;
    std::cin >> u >> v >> t;
    u--;
    v--;
    adj[v].push_back({u, t}); // Reverse edge: v -> u with weight t
  }

  // dis[u] stores distance from Orthanc (node n-1) to node u
  std::vector<long long> dis(n, -1);
  
  // Priority queue for Dijkstra's algorithm (min-heap)
  std::priority_queue<std::pair<long long, int>,
                      std::vector<std::pair<long long, int>>,
                      std::greater<std::pair<long long, int>>>
      pq;
  pq.push({0ll, n - 1}); // Start from Orthanc (index n-1)

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (dis[u] != -1) { // Already processed
      continue;
    }
    dis[u] = d; // Distance from Orthanc is known now

    // Relax all outgoing edges in reverse graph (i.e., check neighbors via adjacency list)
    for (auto [v, w] : adj[u]) {
      pq.push({d + w, v});
    }
  }

  // dp[u] stores the maximum number of "hanging around" choices possible at node u
  std::vector<int> dp(n, -1);
  
  // Deque for processing nodes in topological order (BFS-style with prioritization)
  std::deque<std::array<int, 2>> dq;

  // Initialize deque with all nodes unreachable from Orthanc
  for (int i = 0; i < n; i++) {
    if (dis[i] == -1) {
      dq.push_back({i, 0}); // {node, max_hang_around_count}
    }
  }

  // Compute in-degrees for topological order (number of incoming edges)
  std::vector<int> in(n);
  for (int u = 0; u < n; u++) {
    if (dis[u] == -1) {
      continue;
    }
    for (auto [v, w] : adj[u]) {
      // If v connects to u through a shortest path edge (based on distance)
      if (dis[v] == dis[u] + w) {
        in[v]++;
      }
    }
  }

  while (!dq.empty()) {
    auto [u, d] = dq.front();
    dq.pop_front();

    if (u == n - 1 || dp[u] != -1) { // Reached Orthanc or already computed
      continue;
    }
    
    dp[u] = d;

    for (auto [v, w] : adj[u]) {
      // Add to the back of deque, indicating a potentially independent move
      dq.push_back({v, d + 1});
      if (dis[u] != -1 && dis[v] == dis[u] + w) {
        // Decrease in-degree for v
        if (--in[v] == 0) {
          // If no more dependencies, prioritize this node by pushing to front
          dq.push_front({v, d});
        }
      }
    }
  }

  // If starting node (1) was never reached or couldn't compute value, set to n+1 (infinity)
  if (dp[0] == -1) {
    dp[0] = n + 1;
  }

  std::cout << dp[0] - 1 << "\n";
  return 0;
}


// https://github.com/VaHiX/codeForces/