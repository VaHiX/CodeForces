// Problem: CF 770 C - Online Courses In BSU
// https://codeforces.com/contest/770/problem/C

/*
Algorithm/Techniques: Topological Sorting with Cycle Detection using DFS
Time Complexity: O(n + m) where n is the number of courses and m is the total number of dependencies
Space Complexity: O(n + m) for adjacency list and recursion stack

This code determines the minimum set of courses to take in order to complete a specialty,
considering prerequisites and main courses. It uses a depth-first search (DFS) to perform
a topological sort, detecting cycles in the process. The result is a valid order in which
courses can be taken to satisfy all prerequisites and complete the required main courses.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int maxn = 1e5;
int c[maxn]; // Color array for DFS: 0=unvisited, 1=visiting, 2=visited
vector<int> t; // Stores the topological order
vector<int> g[maxn]; // Adjacency list representing the dependency graph

// DFS function for topological sort and cycle detection
void dfs(int v) {
  if (c[v] == 2) // Already fully processed
    return;
  c[v] = 1; // Mark as visiting
  for (int u : g[v]) { // For each prerequisite
    if (c[u] == 1) { // Cycle detected
      cout << -1 << "\n";
      exit(0);
    }
    dfs(u); // Recursively visit prerequisite
  }
  t.push_back(v); // Add to topological order
  c[v] = 2; // Mark as fully processed
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, k;
  cin >> n >> k;
  vector<int> q; // Main courses to complete
  while (k--) {
    int v;
    cin >> v;
    v--;
    q.push_back(v); // Convert to 0-based indexing
  }
  for (int v = 0; v < n; v++) {
    int m;
    cin >> m;
    while (m--) {
      int u;
      cin >> u;
      u--;
      g[v].push_back(u); // Build adjacency list
    }
  }
  for (int v : q)
    dfs(v); // Start DFS from each main course
  
  cout << t.size() << "\n"; // Output number of courses in order
  for (int v : t)
    cout << v + 1 << " "; // Convert back to 1-based indexing
  cout << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/