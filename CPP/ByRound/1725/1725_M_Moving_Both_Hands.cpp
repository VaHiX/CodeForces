// Problem: CF 1725 M - Moving Both Hands
// https://codeforces.com/contest/1725/problem/M

/*
M. Moving Both Hands
Algorithms/Techniques: Dijkstra's algorithm with modified graph construction
Time Complexity: O((N + M) * log(N))
Space Complexity: O(N + M)

This problem involves finding the shortest time for two hands (starting at vertices 1 and p) 
to meet in a directed graph. The approach uses a modified graph where each node is duplicated 
into two copies: one representing the state where the left hand is here, the other where the right hand is.
Edges between these copies are added to simulate hand movement.

The algorithm applies Dijkstra's shortest path from vertex 1 in this expanded graph to determine
the minimum time for both hands to meet at the same node.
*/
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
#define ll long long
#define INF 1e18
const int N = 2e6 + 10;
int n, m, beg[N], nex[N], to[N], w[N], e;

// Add a directed edge from x to y with weight z
inline void add(int x, int y, int z) {
  ++e;
  nex[e] = beg[x];
  beg[x] = e;
  to[e] = y;
  w[e] = z;
}

ll dis[N];       // Distance array for Dijkstra
int vis[N];      // Visited array for Dijkstra
priority_queue<pair<ll, int>> Q;  // Priority queue for Dijkstra

int main() {
  scanf("%d%d", &n, &m);
  
  // For each vertex v, create two nodes: v and v + n (left and right hand positions)
  for (int i = 1; i <= n; i++)
    add(i, i + n, 0);  // Add zero-weight self-loop to represent the same position

  // Read all edges and construct a bidirectional graph for both hands
  for (int i = 1; i <= m; i++) {
    int u, v, w_val;
    scanf("%d%d%d", &u, &v, &w_val);
    add(u, v, w_val);             // Original edge
    add(v + n, u + n, w_val);     // Reverse edge in the mirrored graph
  }

  // Start Dijkstra from vertex 1 (left hand at 1, right hand also at 1)
  Q.push(make_pair(0, 1));
  
  // Initialize all distances to infinity except for source node
  for (int i = 2; i <= n + n; i++)
    dis[i] = INF;
  
  while (!Q.empty()) {
    int x = Q.top().second;
    Q.pop();
    
    if (vis[x]) continue;
    vis[x] = 1;
    
    // Traverse neighbors
    for (int i = beg[x]; i; i = nex[i]) {
      int t = to[i];
      if (dis[t] > dis[x] + w[i])
        dis[t] = dis[x] + w[i], Q.push(make_pair(-dis[t], t));
    }
  }

  // Output the result for each possible right hand start position
  for (int i = n + 2; i <= n + n; i++)
    printf("%lld ", dis[i] == INF ? -1 : dis[i]);
  
  return 0;
}


// https://github.com/VaHiX/codeForces/