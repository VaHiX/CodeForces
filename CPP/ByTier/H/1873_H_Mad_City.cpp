// Problem: CF 1873 H - Mad City
// https://codeforces.com/contest/1873/problem/H

/*
Purpose: 
This code determines whether Valeriu can escape Marcel forever in a game played on a graph representing a city with buildings and roads. 
Marcel and Valeriu start at different buildings and move optimally. Valeriu knows Marcel's move before deciding his own.

Algorithm:
1. Build an adjacency list representation of the graph.
2. Find a cycle in the graph using DFS (the 'en' variable marks the start of the cycle).
3. Perform BFS from the beginning of the cycle to compute distances from that node.
4. Compare the distance from Marcel's starting position to the cycle with that of Valeriu's starting position.
   If Marcel is farther from the cycle than Valeriu, Valeriu can escape, otherwise, Marcel can catch him.

Time Complexity: O(n) per test case due to linear traversal of the graph for DFS and BFS.
Space Complexity: O(n) for storing the graph and auxiliary arrays.

*/
#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 400010;
int n, s, t, idx, en, h[N], e[N], d[N], ne[N], st[N];

// Add edge to adjacency list
void add(int a, int b) { 
    e[idx] = b, ne[idx] = h[a], h[a] = idx++; 
}

// DFS to detect a cycle in the graph
void dfs(int u, int p) {
  st[u] = 1;
  for (int i = h[u]; ~i; i = ne[i]) {
    int j = e[i];
    if (j == p)
      continue;
    if (en)
      return;
    if (st[j]) {
      en = j;
      return;
    }
    if (!st[j])
      dfs(j, u);
  }
  return;
}

// BFS to calculate distances from a given node
void bfs(int u) {
  queue<int> q;
  q.push(u);
  while (q.size()) {
    u = q.front();
    q.pop();
    st[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
      int j = e[i];
      if (st[j])
        continue;
      st[j] = 1;
      d[j] = d[u] + 1;
      q.push(j);
    }
  }
  return;
}

// Solve function for each test case
void solve() {
  en = 0;
  scanf("%d%d%d", &n, &s, &t);
  for (int i = 1; i <= n; i++)
    h[i] = -1, st[i] = 0;
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    add(a, b);
    add(b, a);
  }
  for (int i = 1; i <= n; i++)
    st[i] = d[i] = 0;
  dfs(t, 0);  // Find the cycle starting from Valeriu's position
  for (int i = 1; i <= n; i++)
    st[i] = 0;
  bfs(en);  // BFS from the start of the cycle to find all distances
  if (d[s] > d[t])
    printf("YES\n");
  else
    printf("NO\n");
}

// Main function to read input and test cases
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/