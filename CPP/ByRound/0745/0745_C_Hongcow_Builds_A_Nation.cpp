// Problem: CF 745 C - Hongcow Builds A Nation
// https://codeforces.com/contest/745/problem/C

/*
Purpose: This code solves the problem of adding maximum edges to a graph while keeping it stable.
         A stable graph ensures no path exists between any two government nodes.
         The solution uses DFS to find connected components, identifies the largest component,
         and computes the maximum possible edges using the formula for complete graphs minus existing edges.

Algorithms/Techniques:
- Depth-First Search (DFS) to identify connected components
- Map to count nodes in each component
- Mathematical formula to compute maximum edges in a complete graph

Time Complexity: O(N + M), where N is number of nodes and M is number of edges
Space Complexity: O(N + M), for adjacency list and auxiliary arrays

*/
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define inf 1000000
#define N 1010
using namespace std;
int color[N]; // Color array to store component id for each node
vector<int> adj[N]; // Adjacency list representation of the graph
bool vis[N]; // Visited array to track visited nodes during DFS

// Function to perform DFS and assign colors (components) to nodes
void dfs(int s, int c) {
  if (vis[s])
    return;
  vis[s] = 1;
  for (int i : adj[s]) {
    if (!vis[i]) {
      color[i] = c;
      dfs(i, c);
    }
  }
}

int main() {
  int i, j, k;
  int n, m;
  int u, v, w;
  scanf("%d%d%d", &n, &m, &k);
  int *g = new int[k]; // Array to store government node ids
  for (i = 0; i < k; i++)
    scanf("%d", &g[i]);
  for (i = 1; i <= n; i++)
    color[i] = 0, vis[i] = 0; // Initialize color and visited arrays
  for (i = 0; i < m; i++) {
    scanf("%d%d", &u, &v);
    adj[u].push_back(v); // Add edge to adjacency list
    adj[v].push_back(u);
  }
  // Assign components to all government nodes and their connected nodes
  for (i = 0; i < k; i++) {
    if (!vis[g[i]]) {
      color[g[i]] = g[i];
      dfs(g[i], g[i]);
    }
  }
  map<int, int> mp; // Map to store count of nodes in each component
  for (i = 1; i <= n; i++) {
    mp[color[i]]++;
  }
  // Find the component with maximum size (starting with first government node)
  j = mp[g[0]];
  u = g[0];
  for (i = 1; i < k; i++) {
    if (mp[g[i]] > j)
      j = mp[g[i]], u = g[i];
  }
  // Merge the largest component with component 0 for calculation
  mp[u] += mp[0];
  mp[0] = 0;
  ll cnt = 0;
  // Calculate total possible edges in each component using complete graph formula
  for (i = 0; i < k; i++) {
    j = mp[g[i]] * (mp[g[i]] - 1) / 2;
    cnt += j;
  }
  // Subtract the existing edges to get the number of new edges that can be added
  printf("%I64d\n", cnt - m);
  return 0;
}


// https://github.com/VaHiX/CodeForces/