// Problem: CF 1666 L - Labyrinth
// https://codeforces.com/contest/1666/problem/L

/*
L. Labyrinth
Algorithms/Techniques: Depth-First Search (DFS) with cycle detection and path reconstruction.

Time Complexity: O(n + m), where n is the number of vertices and m is the number of edges.
Space Complexity: O(n + m), for storing the adjacency list and auxiliary arrays.

The problem asks to find two distinct paths from a starting vertex 's' to some ending vertex 't', 
such that the only common vertices between the paths are 's' and 't'. This is essentially finding 
two disjoint paths from s to some t, not counting s or t themselves. We use DFS to traverse 
the graph and detect when we enter a cycle (a back edge), which means we have found a path 
that connects to an already visited node. Then we can trace back the path from that node to root, 
and also find another path starting from 's' to a different node in its subtree.
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define MAX 1000009
#define zxc(x) cerr << (#x) << '=' << (x) << '\n'
vector<int> E[MAX]; // Adjacency list for the graph
int n, m, s;        // Number of vertices, edges, and start vertex
int vis[MAX], NOW;  // Visited array and time stamp for DFS traversal
int fa[MAX];        // Parent array to track parent in DFS tree
int ans[2][MAX];    // Two arrays storing the two paths

void DFS(int u, int f) {
  if (u == s)
    return;
  if (vis[u]) {   // If current node is already visited
    if (vis[u] != NOW) {   // And it was visited in a different DFS run
      // Reconstruct first path from 'u' to root and store it
      for (int i = u; i; i = fa[i]) {
        ans[0][++ans[0][0]] = i;
      }
      fa[u] = f;   // Update parent of u
      // Reconstruct second path from 'u' to root and store it
      for (int i = u; i; i = fa[i]) {
        ans[1][++ans[1][0]] = i;
      }
      puts("Possible");
      cout << ans[0][0] << '\n';
      while (ans[0][0])
        cout << ans[0][ans[0][0]--] << ' ';
      cout << '\n';
      cout << ans[1][0] << '\n';
      while (ans[1][0])
        cout << ans[1][ans[1][0]--] << ' ';
      cout << '\n';
      exit(0);   // Exit as solution found
    }
    return;
  }
  vis[u] = NOW;  // Mark node as visited in current run
  fa[u] = f;     // Set parent
  for (int v : E[u]) { // Traverse neighbors
    DFS(v, u);
  }
}

signed main() {
  scanf("%d%d%d", &n, &m, &s);
  for (int i = 1; i <= m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    E[a].push_back(b); // Build adjacency list
  }
  for (int v : E[s]) {   // Start DFS from each neighbor of s
    NOW++;
    DFS(v, s);
  }
  puts("Impossible");    // No valid paths found
}


// https://github.com/VaHiX/codeForces/