// Problem: CF 1888 E - Time Travel
// https://codeforces.com/contest/1888/problem/E

/*
 * Problem: E. Time Travel
 * 
 * Purpose: 
 *   This code finds the minimum number of time travels required to reach city n from city 1,
 *   where each travel is associated with a specific moment in time, and roads are only
 *   available at specific time moments.
 * 
 * Algorithm:
 *   - Use Dijkstra's algorithm with a priority queue to find shortest path.
 *   - For each city, we store all time moments in which roads can be traversed to reach
 *     adjacent cities.
 *   - During Dijkstra's traversal, for each adjacent city, we binary search for the 
 *     earliest possible time moment that allows transition from current moment.
 * 
 * Time Complexity: O((V + E) * log V * log T)
 *   - V: number of cities
 *   - E: number of roads
 *   - T: number of time moments (upper bound on the number of transitions)
 * 
 * Space Complexity: O(V + E + T)
 *   - Storage for graph G, time index mapping tim_idx, and auxiliary arrays (dis, vis).
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#define ll long long
using namespace std;
const int N = 2e5 + 5;

// Fast input functions
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0, w = 1;
  char ch = 1;
  while (!isdigit(ch)) {
    if (ch == '-')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}

// Variables
int n, t, m, k;
int dis[N], vis[N];
vector<int> tim_idx[N]; // Maps time moment to list of indices where this moment occurs
vector<pair<int, int>> G[N]; // Graph representation: [neighbor, time_moment]

void init() {}

// Dijkstra's algorithm with time-aware transitions
void Dijkstra() {
  // Initialize distances to -1 (unreachable) and visited flags to 0
  memset(dis + 1, -1, sizeof(int) * n);
  memset(vis + 1, 0, sizeof(int) * n);
  
  // Start distance from city 1 is 1 (first travel)
  dis[1] = 1;
  
  // Priority queue for Dijkstra: [distance, city]
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  pq.push(make_pair(dis[1], 1));
  
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    
    // Skip if already processed
    if (vis[u])
      continue;
      
    vis[u] = true;
    
    // Traverse all neighbors of city u
    for (auto [v, tim] : G[u]) {
      if (!vis[v]) {
        // Binary search for the minimum time index >= current time (d)
        int l = 0, r = (int)tim_idx[tim].size() - 1, p = r + 1;
        while (l <= r) {
          int mid = l + r >> 1;
          if (tim_idx[tim][mid] >= dis[u]) {
            r = mid - 1, p = mid;
          } else
            l = mid + 1;
        }
        
        // If valid transition exists, update distance
        if (p < (int)tim_idx[tim].size()) {
          int ndis = tim_idx[tim][p] + 1;
          if (dis[v] == -1 || dis[v] > ndis) {
            dis[v] = ndis;
            pq.push(make_pair(dis[v], v));
          }
        }
      }
    }
  }
}

// Process input and run main logic
void charming() {
  init();
  n = read(), t = read();
  
  // Read roads for each time moment
  for (int i = 1; i <= t; ++i) {
    m = read();
    for (int j = 1, u, v; j <= m; ++j) {
      u = read(), v = read();
      G[u].emplace_back(make_pair(v, i));
      G[v].emplace_back(make_pair(u, i));
    }
  }
  
  // Read time moments for transitions
  k = read();
  for (int i = 1, a; i <= k; ++i) {
    a = read();
    tim_idx[a].emplace_back(i);
  }
  
  // Run Dijkstra
  Dijkstra();
  
  // Output result
  printf("%d\n", dis[n] == -1 ? -1 : dis[n] - 1);
}

signed main() {
  charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/