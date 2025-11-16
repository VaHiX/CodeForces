// Problem: CF 2014 E - Rendez-vous de Marian et Robin
// https://codeforces.com/contest/2014/problem/E

/*
E. Rendez-vous de Marian et Robin

Purpose:
This code solves the problem of finding the earliest time two people (Marian and Robin) can meet in a graph-based network.
One starts at vertex 1, the other at vertex n. Some vertices have horses that halve travel times once mounted.
The solution uses a modified Dijkstra's algorithm with state tracking for whether each person is on a horse.

Algorithms/Techniques:
- Modified Dijkstra's algorithm using a priority queue
- State space: (distance, who_is_on_horse (0 or 1), has_horse (0 or 1), current_node)
- Bidirectional search approach to find earliest meet time

Time Complexity: O((m + n) * log n)
Space Complexity: O(n + m)

*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

void run() {
  int n, m, h;
  cin >> n >> m >> h;
  vector<bool> horse(n); // tracks which vertices have horses
  while (h--) {
    int x;
    cin >> x;
    horse[x - 1] = 1; // convert to 0-based indexing
  }
  vector<vector<pair<int, int>>> adj(n); // adjacency list with weights
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--; // convert to 0-based indexing
    adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
  }
  vector vis(2, vector(2, vector(n, false))); // visited states: [who][has_horse][node]
  priority_queue<tuple<long long, bool, bool, int>> pq; // priority queue for Dijkstra
  pq.emplace(0, 0, 0, 0), pq.emplace(0, 1, 0, n - 1); // start at 0 with Marian (0) and n-1 with Robin (1)
  while (pq.size()) {
    auto [d, b, ho, u] = pq.top();
    pq.pop();
    d = -d; // negate to get actual distance
    if (vis[b][ho][u])
      continue; // skip if already visited
    if (vis[!b][ho][u] or vis[!b][!ho][u]) { // check if opponent has been here
      cout << d << '\n';
      return;
    }
    vis[b][ho][u] = 1; // mark current state as visited
    ho |= horse[u]; // if current vertex has a horse, update horse status
    for (auto [v, w] : adj[u]) { // traverse neighbors
      pq.emplace(-(d + (ho ? w / 2 : w)), b, ho, v); // add next state with updated distance
    }
  }
  cout << "-1\n"; // no meeting point found
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--)
    run();
}


// https://github.com/VaHiX/codeForces/