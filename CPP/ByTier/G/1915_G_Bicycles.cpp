// Problem: CF 1915 G - Bicycles
// https://codeforces.com/contest/1915/problem/G

/*
 * Problem: G. Bicycles
 * 
 * Purpose: Find the shortest time for Slavic to travel from city 1 to city n,
 *          considering that he can buy bikes in each city with different slowness factors.
 *          When traveling on an edge, the time taken is weight * current_bike_slowness.
 * 
 * Algorithm: Modified Dijkstra's algorithm using a priority queue.
 *            State is represented as (city, current_max_slowness_factor).
 *            We track the minimum time to reach each (city, slowness) pair.
 * 
 * Time Complexity: O((V + E) * max_slowness * log(V * max_slowness))
 *                  Where V = number of cities, E = number of edges, max_slowness = 1000
 * Space Complexity: O(V * max_slowness)
 * 
 * Techniques: Dijkstra with state optimization, priority queue with custom comparator
 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAX_SLOWNESS 1005

struct edge {
  int v;
  int w;
};

struct node {
  int u;
  int slowness;
  long long int time;
};

class MyComparator {
public:
  int operator()(const node &n1, const node &n2) { return n1.time > n2.time; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);
    vector<int> slowness(n);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      graph[u - 1].push_back(edge{v - 1, w});
      graph[v - 1].push_back(edge{u - 1, w});
    }
    for (int i = 0; i < n; i++)
      cin >> slowness[i];
    bool visited[n][MAX_SLOWNESS];
    memset(visited, 0, sizeof(visited));
    priority_queue<node, vector<node>, MyComparator> Q;
    Q.push(node{0, MAX_SLOWNESS, 0}); // Start with initial slowness factor set to a large value
    long long int ans = 0;
    while (!Q.empty()) {
      node nd = Q.top();
      Q.pop();
      // Update current slowness as the minimum of previous and current city's bike slowness
      int cur_slowness = min(nd.slowness, slowness[nd.u]);
      if (visited[nd.u][cur_slowness])
        continue;
      visited[nd.u][cur_slowness] = 1;
      if (nd.u == n - 1) { // Reached destination
        ans = nd.time;
        break;
      }
      for (int i = 0; i < graph[nd.u].size(); i++) {
        int v = graph[nd.u][i].v;
        int w = graph[nd.u][i].w;
        if (!visited[v][cur_slowness]) {
          long long int time = w * cur_slowness; // Time to cross edge with current bike
          Q.push(node{v, cur_slowness, nd.time + time});
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/