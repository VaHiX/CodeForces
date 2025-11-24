// Problem: CF 1006 E - Military Problem
// https://codeforces.com/contest/1006/problem/E

/*
 * Problem: E. Military Problem
 * 
 * Purpose: This code organizes a command delivery system for the Berland army,
 *          where the structure is a tree rooted at officer 1 (the commander).
 *          For each query (u, k), it determines the k-th officer to receive a command
 *          when officer u starts spreading it using a specific DFS traversal order.
 * 
 * Algorithms/Techniques:
 *   - Tree representation using adjacency lists
 *   - Preprocessing using DFS to compute in-order traversal and subtree sizes
 *   - Efficient query processing using precomputed arrays
 * 
 * Time Complexity: O(n log n + q)
 *   - O(n log n) for sorting children of each node during preprocessing
 *   - O(n) for DFS traversal
 *   - O(1) per query after preprocessing
 * 
 * Space Complexity: O(n)
 *   - Storage for adjacency list, traversal order, and subtree sizes
 * 
 */

#include <algorithm>
#include <cstdio>
#include <vector>

// Performs DFS to build traversal order and compute subtree sizes
void dfs(const std::vector<std::vector<long>> &g, long cur,
         std::vector<long> &rank, std::vector<long> &below) {
  rank.push_back(cur);  // Add current node to traversal order
  for (long p = 0; p < g[cur].size(); p++) {
    long node = g[cur][p];
    dfs(g, g[cur][p], rank, below);  // Recursively process subtree
    below[cur] += below[node];  // Accumulate subtree size
  }
}

int main() {
  long n, q;
  scanf("%ld %ld", &n, &q);
  std::vector<std::vector<long>> g(n + 1);  // Adjacency list for tree

  // Read parent information and build adjacency list
  for (long p = 2; p <= n; p++) {
    long x;
    scanf("%ld", &x);
    g[x].push_back(p);
  }
  
  // Sort children in ascending order to ensure consistent traversal
  for (long p = 1; p <= n; p++) {
    sort(g[p].begin(), g[p].end());
  }

  // Precompute traversal order and subtree sizes
  std::vector<long> pos(1, 0), below(n + 1, 1);  // pos: traversal order, below: subtree sizes
  dfs(g, 1, pos, below);  // Start DFS from root (officer 1)

  // Map traversal index to officer number
  std::vector<long> v(n + 1, 0);
  for (long p = 1; p <= n; p++) {
    v[pos[p]] = p;
  }

  // Process queries
  while (q--) {
    long u, k;
    scanf("%ld %ld", &u, &k);
    
    // Check if k-th officer exists in subtree of u
    if (below[u] < k) {
      puts("-1");
      continue;
    }
    
    // Calculate position in traversal and output the officer
    long where = v[u] + k - 1;
    printf("%ld\n", pos[where]);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/