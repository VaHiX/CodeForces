// Problem: CF 512 A - Fox And Names
// https://codeforces.com/contest/512/problem/A

/*
 * Problem: Fox And Names
 * 
 * Purpose: Determine if there exists a lexicographical ordering of the alphabet such that
 *          a given list of names is sorted in that order. If yes, output one such ordering.
 *          Otherwise, output "Impossible".
 * 
 * Approach:
 *   1. Build a directed graph where each node represents a letter.
 *   2. For each adjacent pair of names, find the first differing character and add a directed edge
 *      from the character in the earlier name to the one in the later name.
 *   3. Perform topological sort on the graph to get a valid ordering of letters.
 *   4. If a cycle is detected during DFS traversal, it's impossible.
 * 
 * Algorithms/Techniques:
 *   - Topological Sort using DFS
 *   - Graph construction from lexicographical comparison
 *   - Cycle detection in directed graph
 * 
 * Time Complexity: O(N * M + 26^2) where N is number of names, M is average name length.
 * Space Complexity: O(26^2 + N * M) for adjacency list and input storage.
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int n, vi[26];                    // vi: visited array for DFS; 0 = unvisited, 1 = visiting, 2 = visited
string s, t;                       // s: current name, t: next name
stack<int> topo;                   // topo: stack for topological order
vector<int> g[26];                 // g: adjacency list for graph representation

// DFS for topological sort with cycle detection
void dfs(int u) {
  vi[u] = 1;                       // Mark node as being visited
  for (auto v : g[u]) {            // Iterate through neighbors
    if (vi[v] == 1) {              // If neighbor is currently being visited -> cycle detected
      cout << "Impossible";
      exit(0);
    }
    if (!vi[v])                    // If neighbor is unvisited
      dfs(v);                      // Visit it
  }
  topo.push(u);                    // Push to stack after DFS finishes
  vi[u] = 2;                       // Mark as fully visited
}

// Add an edge from first differing character of u to v
void addEdge(string u, string v) {
  for (int i = 0; i < min(u.size(), v.size()); i++)
    if (u[i] != v[i]) {            // Find first different character
      g[u[i] - 'a'].push_back(v[i] - 'a'); // Add directed edge
      return;
    }
  if (u.size() > v.size()) {       // Invalid case: prefix longer than suffix
    cout << "Impossible";
    exit(0);
  }
}

signed main() {
  cin >> n >> s;                     // Read first name
  while (n-- - 1) {                  // Process remaining names
    cin >> t;
    addEdge(s, t);                   // Create edge based on current pair
    s = t;                           // Update s to t for next iteration
  }
  
  for (int i = 0; i < 26; i++)       // Start DFS for all unvisited nodes
    if (!vi[i])
      dfs(i);
      
  while (!topo.empty()) {            // Output topological order
    cout << char(topo.top() + 'a');
    topo.pop();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/