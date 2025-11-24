// Problem: CF 931 D - Peculiar apple-tree
// https://codeforces.com/contest/931/problem/D

/*
Code Purpose:
This code solves the problem of counting how many apples will reach the base of a peculiar apple-tree after following a set of rules. 
Each inflorescence (node) has an apple that rolls down along a tree structure to the root (node 1). 
If multiple apples reach the same node at the same time, they annihilate pairwise, leaving only one apple if the count is odd, or none if even.

Approach:
- Build a tree from input edges.
- Perform DFS from root (node 1) to compute the depth of each node.
- For each depth level, count how many apples would arrive.
- Since apples annihilate in pairs, only odd counts contribute to the final result.
- The answer is the number of depths where an odd number of apples arrive.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques:
- Tree construction using adjacency list.
- Depth-First Search (DFS) to calculate distances from root.
- Map to track number of apples at each depth.
*/

#include <cstdio>
#include <map>
#include <vector>
#include <utility>

void dfs(long node, long from, long cur,
         const std::vector<std::vector<long>> &g, std::map<long, long> &dist) {
  ++dist[cur]; // Increment count for the current depth level
  for (long p = 0; p < g[node].size(); p++) {
    long u = g[node][p];
    if (u == from) {
      continue; // Skip the parent node to avoid cycle
    }
    dfs(u, node, cur + 1, g, dist); // Recurse to child with increased depth
  }
  return;
}
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> g(n + 1);
  for (long p = 2; p <= n; p++) {
    long r;
    scanf("%ld", &r);
    g[p].push_back(r); // Add edge from p to its parent r
    g[r].push_back(p); // Add edge from r to p (undirected)
  }
  std::map<long, long> dist;
  dfs(1, 0, 0, g, dist); // Start DFS from root node 1 with initial depth 0
  long total(0);
  for (std::map<long, long>::iterator it = dist.begin(); it != dist.end();
       it++) {
    total += ((it->second) & 1); // Add 1 if odd count, 0 if even
  }
  printf("%ld\n", total);
  return 0;
}


// https://github.com/VaHiX/CodeForces/