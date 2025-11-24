// Problem: CF 1144 F - Graph Without Long Directed Paths
// https://codeforces.com/contest/1144/problem/F

/*
Algorithm: Bipartite Check using DFS
Time Complexity: O(n + m) where n is number of vertices and m is number of edges
Space Complexity: O(n + m) for adjacency list and auxiliary arrays

The problem asks to orient edges of a connected undirected graph such that
there are no directed paths of length 2 or more. This is equivalent to
checking if the graph is bipartite. If it's bipartite, we can assign directions
to edges such that no two adjacent vertices have the same "color".

We perform a DFS-based bipartite check:
1. Color vertices with two colors (1 and 2)
2. If we can color all vertices without conflict, it's bipartite
3. Otherwise, we can't orient edges to avoid long paths
4. For output, we use color assignment to decide edge direction
   - If color[u] < color[v], direct edge from u to v (output 0)
   - Else direct edge from v to u (output 1)
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
vector<int> v[200005]; // adjacency list
int a[200005];         // color array (1 or 2)
pair<int, int> e[200005]; // stores edges
bool vis[200005];      // visited array
int n, m;

// DFS to color the graph with two colors (bipartite check)
void dfs(int x, int f) {
  a[x] = f;           // assign color f to vertex x
  vis[x] = 1;         // mark as visited
  for (int i : v[x])  // iterate through neighbors
    if (!vis[i])      // if not visited
      dfs(i, 3 - f);  // color with opposite color (3-1=2, 3-2=1)
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &e[i].first, &e[i].second);
    v[e[i].first].push_back(e[i].second);  // build adjacency list
    v[e[i].second].push_back(e[i].first);  // undirected graph
  }
  dfs(1, 1);  // start DFS from vertex 1 with color 1

  // Check if the coloring is valid (bipartite)
  for (int i = 0; i < m; i++)
    if (a[e[i].first] == a[e[i].second]) // if both ends have same color
      return puts("NO"), 0;              // not bipartite, impossible

  puts("YES");  // graph is bipartite

  // Output edge directions (0: u->v, 1: v->u)
  for (int i = 0; i < m; i++)
    cout << a[e[i].first] - 1;  // if a[u] > a[v], then u->v, else v->u
  return 0;
}


// https://github.com/VaHiX/CodeForces/