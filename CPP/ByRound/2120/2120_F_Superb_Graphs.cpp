// Problem: CF 2120 F - Superb Graphs
// https://codeforces.com/contest/2120/problem/F

/*
F. Superb Graphs
Algorithm: 2-SAT (Satisfiability with constraints on pairs of variables)
Techniques: Tarjan's algorithm for finding strongly connected components (SCC)

Time Complexity: O(n^2 * k + m) where n is number of vertices and m is total edges across all graphs
Space Complexity: O(n^2 + n * k) for graph representation and auxiliary arrays

The problem involves checking if there exists a set of k graphs such that:
1. Each given graph G_i is a superb graph of some H_i
2. For each vertex v, if it maps to an independent set of size > 1 in one G_i, then v must map to a clique of size <= 1 in all other H_j

We model this using 2-SAT:
- Each vertex v in original graph creates two boolean variables representing: 
  v_true: whether v corresponds to a clique (in some H_i)
  v_false: whether v corresponds to an independent set (in some H_i)  
- For each pair of vertices u,v that appear together or separately in all graphs:
  we must enforce one of these constraints:
    - If u and v are connected in every G_i, then in corresponding H_i they should form a clique
    - If u and v are not connected in every G_i, then they should be part of independent sets
This is encoded into implications between variables using 2-SAT.
*/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
int a[301][301]; // adjacency matrix for current graph being processed
vector<int> g[601]; // the 2-SAT implication graph, 2*n nodes (variables and negations)
int dfn[601], low[601], st[601], ins[601]; 
// dfn: discovery time, low: lowest reachable vertex in SCC, st: stack for Tarjan's algorithm, ins: stack membership

void dfs(int u) {
  // Standard DFS to find strongly connected components using Tarjan's algorithm
  low[u] = dfn[u] = ++dfn[0]; // set discovery and low values
  st[++st[0]] = u; // push onto stack
  ins[u] = 1;
  for (int i = 0; i < g[u].size(); i++) {
    if (!dfn[g[u][i]]) 
      dfs(g[u][i]); // DFS on unvisited neighbor
    if (ins[g[u][i]])
      low[u] = min(low[u], low[g[u][i]]); // Update low value if neighbor is still in stack
  }
  if (low[u] == dfn[u]) {
    // Found Strongly Connected Component
    while (st[st[0] + 1] != u) { 
      ins[st[st[0]]] = 0; // Pop from stack
      low[st[st[0]]] = u; // Assign component ID
      st[0]--;
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++) {
    int n, k;
    scanf("%d%d", &n, &k);
    
    dfn[0] = 0; // Reset time counter
    for (int i = 1; i <= 2 * n; i++) {
      g[i].clear(); // Clear implication graph
      st[i] = 0;
      dfn[i] = 0;
    }
    
    // Process each of the k graphs
    for (int i = 1; i <= k; i++) {
      int m;
      scanf("%d", &m);
      
      // Reset adjacency matrix for this graph
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
          a[i][j] = 0;
      
      // Read edges of the current graph
      for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        a[u][v] = a[v][u] = 1; // Undirected edge
      }
      
      // For each pair of vertices (i,j), determine their relationship across all graphs
      for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
          // Check if i and j have same connection status in this graph
          bool same = true;
          int same_edge_status = a[i][j]; 
          
          // For each vertex k != i,j, check if the edge pattern matches with current graph's edge (i,j)
          for (int k = 1; k <= n; k++)
            if (k != i && k != j && a[i][k] != a[j][k]) {
              same = false; // Conflict exists
              goto ed;      // Jump to end of inner loop
            }
          
          if (same) {
            // Vertices i and j are always in same state across all graphs -> can be connected in both or not
            if (a[i][j]) {
              // If connected in all graphs, they must correspond to cliques
              g[i + n].push_back(j);  // i is a clique => j also
              g[j + n].push_back(i);  // j is a clique => i also
            } else {
              // If disconnected in all, they must be independent sets 
              g[i].push_back(j + n); // i is independent => j is not clique 
              g[j].push_back(i + n); // j is independent => i is not clique
            }
          }
        ed:;
        }
    }
    
    // Run Tarjan's algorithm on implication graph to find SCCs
    for (int i = 1; i <= 2 * n; i++)
      if (!dfn[i])
        dfs(i);
    
    // Check if solution exists using 2-SAT constraints
    int ok = 1;
    for (int i = 1; i <= n; i++)
      if (low[i] == low[i + n]) // Cannot satisfy both x and ~x in same SCC  
        ok = 0;
    
    printf(ok ? "Yes\n" : "No\n");
  }
}


// https://github.com/VaHiX/codeForces/