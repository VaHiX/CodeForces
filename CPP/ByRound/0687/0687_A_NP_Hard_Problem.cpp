// Problem: CF 687 A - NP-Hard Problem
// https://codeforces.com/contest/687/problem/A

/*
 * Problem: Splitting a graph into two vertex covers
 * 
 * Purpose: Given an undirected graph, determine if it's possible to split the vertices into two disjoint sets such that both sets form a vertex cover.
 * 
 * Algorithm:
 * 1. Model the problem as checking if the graph is bipartite.
 * 2. If the graph is bipartite, we can assign vertices to two sets (A and B) such that no edge connects vertices within the same set.
 * 3. These two sets will both be vertex covers because for every edge, one endpoint is in A and the other in B.
 * 4. If the graph is not bipartite, it's impossible to split it into two vertex covers.
 * 
 * Time Complexity: O(n + m) - Each vertex and edge is processed once during the DFS traversal.
 * Space Complexity: O(n + m) - For storing adjacency list and coloring information.
 */

#include <cstdio>
#include <vector>

// DFS function to check if the graph is bipartite and assign colors to vertices
// Parameters:
//   g: adjacency list of the graph
//   x: current vertex
//   r: color array (-1 = unvisited, 0 = color 0, 1 = color 1)
// Returns:
//   true if the subgraph is bipartite, false otherwise
bool dfs(const std::vector<std::vector<long>> &g, long x, std::vector<int> &r) {
  if (r[x] < 0) {
    return false;
  }
  for (long p = 0; p < g[x].size(); p++) {
    long y = g[x][p];
    if (r[y] < 0) {
      r[y] = 1 - r[x];  // Assign opposite color
      bool temp = dfs(g, y, r);
      if (!temp) {
        return false;
      }
    } else if (r[y] == r[x]) {
      return false;  // Conflict: adjacent vertices have same color
    }
  }
  return true;
}

int main() {
  long n, m;
  scanf("%ld %ld\n", &n, &m);
  std::vector<std::vector<long>> graph(n + 1);  // Adjacency list
  for (long p = 0; p < m; p++) {
    long x, y;
    scanf("%ld %ld\n", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  std::vector<int> part(n + 1, -1);  // Color array, -1 = unvisited
  bool possible(1);
  
  // Check each connected component
  for (long p = 1; p <= n; p++) {
    if (part[p] >= 0) {
      continue;  // Skip already visited
    }
    part[p] = 0;  // Start with color 0
    bool t = dfs(graph, p, part);
    if (!t) {
      possible = 0;
      break;
    }
  }
  
  if (!possible) {
    printf("-1\n");
    return 0;
  }
  
  // Partition the vertices based on their color
  std::vector<long> left;
  std::vector<long> right;
  for (long p = 1; p <= n; p++) {
    if (part[p] == 0) {
      left.push_back(p);
    } else {
      right.push_back(p);
    }
  }
  
  // Output the two vertex covers
  printf("%ld\n", left.size());
  for (long p = 0; p < left.size(); p++) {
    printf("%ld ", left[p]);
  }
  printf("\n%ld\n", right.size());
  for (long p = 0; p < right.size(); p++) {
    printf("%ld ", right[p]);
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/CodeForces/