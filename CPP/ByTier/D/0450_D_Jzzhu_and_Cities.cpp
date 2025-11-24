// Problem: CF 450 D - Jzzhu and Cities
// https://codeforces.com/contest/450/problem/D

/*
Purpose: This code solves the problem of determining the maximum number of train routes that can be closed without changing the shortest path from any city to the capital (city 1). It uses a modified Dijkstra's algorithm to track which train routes are essential.

Algorithms/Techniques: Modified Dijkstra's algorithm with priority queue for shortest path calculation.
                       Uses a boolean flag to track if a city is reachable via a train route.

Time Complexity: O((V + E) * log V) where V is the number of cities and E is the number of roads.
Space Complexity: O(V + E) for storing adjacency list and distance array.
*/

#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

typedef long long int ll;
#define inf 1000000000000000
using namespace std;

struct node {
  ll At, cost;
  node(ll where, ll price) {
    At = where;
    cost = price;
  }
};

struct edge {
  ll w, v, isRail;
  edge(ll a, ll b, bool f) {
    v = a;
    w = b;
    isRail = f;
  }
};

bool operator<(node a, node b) { return a.cost > b.cost; }

ll n, m, cr = 0;
ll dist[100010];
bool train[100010];
vector<edge> adj[100010];
priority_queue<node> pq;

void dijkstra(ll s) {
  for (int i = 0; i <= n; i++)
    dist[i] = inf;
  dist[s] = 0;
  pq.push(node(s, dist[s]));
  while (!pq.empty()) {
    node u = pq.top();
    pq.pop();
    if (u.cost != dist[u.At])
      continue;
    for (edge e : adj[u.At]) {
      if (dist[e.v] > u.cost + e.w) {
        if (e.isRail)
          train[e.v] = 1;
        dist[e.v] = u.cost + e.w;
        pq.push(node(e.v, dist[e.v]));
      }
      // If a shorter path is found and the destination was previously reached via train, update train flag
      if (dist[e.v] == u.cost + e.w && train[e.v] && !e.isRail) {
        train[e.v] = 0;
        dist[e.v] = u.cost + e.w;
        pq.push(node(e.v, dist[e.v]));
      }
    }
  }
}

int main() {
  ll i, j, k;
  ll s, e, w;
  cin >> n >> m >> k;
  for (i = 1; i <= m; i++) {
    cin >> s >> e >> w;
    adj[e].push_back(edge(s, w, 0));
    adj[s].push_back(edge(e, w, 0));
  }
  for (i = 1; i <= k; i++) {
    cin >> e >> w;
    adj[e].push_back(edge(1, w, 1));
    adj[1].push_back(edge(e, w, 1));
  }
  memset(train, 0, sizeof(train));
  dijkstra(1);
  ll count = 0;
  for (i = 1; i <= n; i++) {
    if (train[i])
      count++;
  }
  cout << (k - count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/