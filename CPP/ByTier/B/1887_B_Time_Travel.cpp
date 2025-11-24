// Problem: CF 1887 B - Time Travel
// https://codeforces.com/contest/1887/problem/B

/*
Purpose: 
  This code solves a time-travel problem in a graph where roads between cities change over time. 
  The goal is to find the minimum number of time travels needed to reach city n from city 1, 
  considering that you may only move along roads available at each time moment.

Algorithms/Techniques:
  - Graph representation with time-aware edges.
  - BFS-like traversal using time buckets (q[t]) to process nodes at each time moment.
  - State tracking with visited array to avoid revisiting nodes.

Time Complexity: O(N + M + K), where:
  - N = number of cities, 
  - M = total number of edges across all time moments,
  - K = number of time travel steps.

Space Complexity: O(N + M + T), for storing graph edges and time buckets.

*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define INF 1234567890
#define ll long long

int N, T, K;
// g[i] stores edges at time i with destination and time
vector<pair<int, int>> g[200201];
// vis[n] tracks if node n has been visited
bool vis[200201];
// q[t] stores nodes reachable at time t
vector<int> q[200201];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin.exceptions(ios::badbit | ios::failbit);
  
  cin >> N >> T;
  
  // Read edges for each time moment and populate the graph
  for (int i = 1; i <= T; i++) {
    int M;
    cin >> M;
    while (M--) {
      int a, b;
      cin >> a >> b;
      g[a].push_back({b, i});
      g[b].push_back({a, i});
    }
  }
  
  // Mark city 1 as visited and initialize time bucket
  vis[1] = true;
  for (auto [next, cost] : g[1])
    q[cost].push_back(next);
    
  cin >> K;
  
  // Process each time travel step
  for (int i = 1; i <= K; i++) {
    int t;
    cin >> t;
    vector<int> v;
    
    // Traverse all nodes from previous time bucket
    for (int n : q[t])
      if (!vis[n]) {
        vis[n] = true;
        if (n == N) {
          cout << i << "\n";
          return 0;
        }
        v.push_back(n);
      }
    
    // Clear processed nodes from the bucket
    q[t].clear();
    
    // Add neighbors of newly visited nodes to next time bucket
    for (int n : v)
      for (auto [next, cost] : g[n])
        q[cost].push_back(next);
  }
  
  // If we reach here, we couldn't reach city N
  cout << "-1\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/