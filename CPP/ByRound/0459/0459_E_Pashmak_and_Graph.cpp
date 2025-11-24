// Problem: CF 459 E - Pashmak and Graph
// https://codeforces.com/contest/459/problem/E

/*
 * Problem: Pashmak and Graph
 * 
 * Description:
 * Given a weighted directed graph with n vertices and m edges, find the maximum number of edges 
 * in a path such that the weights of the edges strictly increase along the path.
 * 
 * Approach:
 * This is a dynamic programming problem on a DAG (directed acyclic graph). We process edges 
 * in increasing order of their weights and for each weight group, we compute the longest path 
 * ending at each vertex using previously computed values. 
 * 
 * We use a map to store edges grouped by weight, then iterate through weights. For each weight 
 * group, we calculate how far we can go from each starting vertex, and update the maximum 
 * path length seen so far.
 * 
 * Time Complexity: O(m * log m) where m is the number of edges. Log factor comes from map operations.
 * Space Complexity: O(n + m) for storing the graph and auxiliary arrays.
 */

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  // Map to store edges grouped by weight
  std::map<long, std::vector<std::pair<long, long>>> g;
  for (long p = 0; p < m; p++) {
    long u, v, w;
    scanf("%ld %ld %ld", &u, &v, &w);
    g[w].push_back(std::make_pair(u, v));
  }
  // f[v] stores the longest path ending at vertex v
  std::vector<long> f(n + 1, 0), cur(n + 1, 0);
  long maxLength(0);
  
  // Iterate through edges sorted by weight
  for (std::map<long, std::vector<std::pair<long, long>>>::iterator it =
           g.begin();
       it != g.end(); it++) {
    const std::vector<std::pair<long, long>> edges = it->second;
    // Reset cur array for current weight group
    for (long p = 0; p < edges.size(); p++) {
      cur[edges[p].second] = 0;
    }
    // Compute the length of paths ending in each vertex in this weight group
    for (long p = 0; p < edges.size(); p++) {
      long u = edges[p].first;
      long v = edges[p].second;
      cur[v] = (cur[v] > f[u] + 1) ? cur[v] : (f[u] + 1);
    }
    // Update global maximum and f array
    for (long p = 0; p < edges.size(); p++) {
      long u = edges[p].first;
      long v = edges[p].second;
      f[v] = (f[v] > cur[v]) ? f[v] : cur[v];
      maxLength = (maxLength > f[v]) ? maxLength : f[v];
    }
  }
  printf("%ld\n", maxLength);
  return 0;
}


// https://github.com/VaHiX/CodeForces/