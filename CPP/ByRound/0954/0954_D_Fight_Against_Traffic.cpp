// Problem: CF 954 D - Fight Against Traffic
// https://codeforces.com/contest/954/problem/D

/*
 * Code Purpose: 
 *   This program computes the number of pairs of junctions that are not directly connected by a road,
 *   such that adding a new road between them will not decrease the shortest distance between
 *   junctions 's' and 't'. It uses BFS to compute shortest distances from 's' and 't', then iterates
 *   through all possible pairs of unconnected junctions to check if adding a road between them
 *   preserves the distance between 's' and 't'.
 *
 * Algorithms:
 *   - BFS (Breadth-First Search) for computing shortest distances from 's' and 't'
 *   - Brute-force pair checking for all unconnected pairs
 *
 * Time Complexity: O(n^2 + m) where n is the number of junctions and m is the number of roads.
 *   - BFS is O(n + m)
 *   - Checking all pairs takes O(n^2)
 *
 * Space Complexity: O(n^2) for adjacency matrix g and O(n) for BFS queues and distance arrays.
 */
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
int q[1010], d1[1010], d2[1010], g[1010][1010], n, m, s, t, cnt;

// BFS to compute shortest distances from a starting node 's' to all other nodes
void bfs(int s, int *d) {
  memset(d, 0x3f, 1010 * 4); // Initialize distances to infinity
  int tt = -1, ww = 0;
  q[0] = s;
  d[s] = 0; // Distance to start node is 0
  while (tt < ww) {
    int x = q[++tt]; // Dequeue node
    for (int i = 1; i <= n; i++)
      if (g[x][i] && d[i] == 0x3f3f3f3f) { // If neighbor is connected and not visited
        d[i] = d[x] + 1; // Update distance
        q[++ww] = i; // Enqueue neighbor
      }
  }
}

int main() {
  cin >> n >> m >> s >> t;
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u][v] = g[v][u] = 1; // Mark road as bidirectional
  }
  bfs(s, d1); // Compute distances from 's'
  bfs(t, d2); // Compute distances from 't'
  
  // Check all pairs of unconnected junctions
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) // Only check upper triangle to avoid duplicates
      if (d1[i] + d2[j] + 1 >= d1[t] && d2[i] + d1[j] + 1 >= d1[t] && !g[i][j]) 
        // If adding road (i,j) does not shorten the path from s to t
        cnt++; // Increment count of valid pairs
  
  cout << cnt << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/