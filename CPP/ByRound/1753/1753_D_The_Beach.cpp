// Problem: CF 1753 D - The Beach
// https://codeforces.com/contest/1753/problem/D

/*
Algorithm: Dijkstra's shortest path algorithm on a graph where each cell is a node, and edges represent possible moves of sunbeds.
Time Complexity: O(nm * log(nm)) due to Dijkstra's algorithm with a priority queue.
Space Complexity: O(nm) for storing the graph and distance array.

This code finds the minimum discomfort required to make a 2-cell space free for Andrew's sunbed.
It models the problem as a graph where each cell is a node and transitions (rotation or shift) are edges with weights p and q.
*/
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int N = 3e5 + 5;
int n, m, p, q, v[N];
long long d[N], ans = 1e18;
vector<pair<int, int>> e[N];  // adjacency list: {node, weight}
priority_queue<pair<long long, int>> c;  // priority queue for Dijkstra: {negative_distance, node}

int main() {
  scanf("%d%d%d%d", &n, &m, &p, &q);
  auto get = [&](int x, int y) { return (x - 1) * m + y; };  // converts 2D coordinates to 1D index
  
  for (int i = 1; i <= n; i++) {
    char s[N];
    scanf("%s", s + 1);
    for (int j = 1; j <= m; j++) {
      d[get(i, j)] = s[j] == '.' ? (c.emplace(0, get(i, j)), 0) : 1e18;  // initialize distance for free cells to 0
      auto add = [&](int x, int y, int z) {
        if (x > 0 && x <= n && y > 0 && y <= m)
          e[get(x, y)].emplace_back(get(i, j), z);  // add edge from neighbor to current cell
      };
      if (s[j] == 'L')
        add(i - 1, j + 1, p), add(i + 1, j + 1, p), add(i, j + 2, q);  // possible moves for left half sunbed
      if (s[j] == 'R')
        add(i - 1, j - 1, p), add(i + 1, j - 1, p), add(i, j - 2, q);  // possible moves for right half sunbed
      if (s[j] == 'U')
        add(i + 1, j - 1, p), add(i + 1, j + 1, p), add(i + 2, j, q);  // possible moves for up half sunbed
      if (s[j] == 'D')
        add(i - 1, j - 1, p), add(i - 1, j + 1, p), add(i - 2, j, q);  // possible moves for down half sunbed
    }
  }
  
  // Dijkstra's algorithm to compute minimum discomfort to reach each cell
  while (c.size()) {
    int x = c.top().second;
    c.pop();
    if (v[x])
      continue;
    v[x] = 1;
    for (auto [y, z] : e[x])
      if (d[x] + z < d[y])
        d[y] = d[x] + z, c.emplace(-d[y], y);
  }
  
  // Find minimum sum of distances for adjacent free cells (a valid placement for sunbed)
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      if (i < n)
        ans = min(ans, d[get(i, j)] + d[get(i + 1, j)]);  // check vertical neighbors
      if (j < m)
        ans = min(ans, d[get(i, j)] + d[get(i, j + 1)]);  // check horizontal neighbors
    }
    
  printf("%lld\n", ans < 1e18 ? ans : -1);  // print result or -1 if not possible
  return 0;
}


// https://github.com/VaHiX/CodeForces/