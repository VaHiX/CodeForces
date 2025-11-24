// Problem: CF 2071 C - Trapmigiano Reggiano
// https://codeforces.com/contest/2071/problem/C

/*
 * Problem: Trapmigiano Reggiano
 * Description:
 *   In a tree with n vertices, a mouse starts at vertex 'st' and must be caught at vertex 'en'.
 *   A permutation p of length n determines the order in which cheese appears.
 *   At each step i, if mouse is already at p[i], it stays; otherwise, it moves towards p[i] one edge closer.
 *   Goal: Find such a permutation that the mouse ends up at 'en' after all steps.
 *
 * Algorithm:
 *   - Build adjacency list representation of the tree.
 *   - Compute distances from target vertex 'en' using DFS.
 *   - Sort vertices in descending order of their distances from 'en'.
 *   - Output this sorted order as the permutation.
 *
 * Time Complexity: O(n log n) per test case due to sorting;
 *                  O(n) for tree construction and distance computation.
 * Space Complexity: O(n) for storing graph, distances, and auxiliary arrays.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

void dfs(long node, long from, const std::vector<std::vector<long>> &g,
         std::vector<long> &dist) {
  for (long nxt : g[node]) {
    if (nxt == from) {
      continue;
    }
    dist[nxt] = dist[node] + 1; // Distance increases by one step
    dfs(nxt, node, g, dist);   // Recursively visit neighbors
  }
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, s, t;
    scanf("%ld %ld %ld", &n, &s, &t);
    --s;
    --t;
    std::vector<std::vector<long>> g(n);
    for (long p = 1; p < n; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      g[x - 1].push_back(y - 1); // Add undirected edge
      g[y - 1].push_back(x - 1);
    }
    std::vector<long> dist(n, 0);
    dfs(t, t, g, dist); // Compute distances from target vertex 't'
    std::vector<std::pair<long, long>> dv(n);
    for (long p = 0; p < n; p++) {
      dv[p] = std::make_pair(dist[p], p); // Pair distance with node index
    }
    sort(dv.rbegin(), dv.rend()); // Sort in descending order by distance
    for (long p = 0; p < n; p++) {
      printf("%ld ", 1 + dv[p].second); // Output actual vertex numbers (1-indexed)
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/