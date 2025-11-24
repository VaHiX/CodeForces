// Problem: CF 2127 D - Root was Built by Love, Broken by Destiny
// https://codeforces.com/contest/2127/problem/D

/*
D. Root was Built by Love, Broken by Destiny
Algorithms/Techniques: Graph theory, Tree properties, Combinatorics, DFS/BFS
Time Complexity: O(n + m) amortized over all test cases
Space Complexity: O(n + m)

Problem Summary:
We are given a graph with n houses and m bridges connecting them. The goal is to count the number of valid ways 
to assign each house to either the northern or southern side such that:
1. Each bridge connects two houses on opposite sides.
2. No two bridges cross when drawn as straight lines (i.e., the arrangement corresponds to a planar embedding where 
   all edges go between sides).
   
If we interpret this as placing n vertices along a line (representing the river), then for a valid planar embedding, 
the graph must be a tree. In fact, any valid configuration means that the induced bipartition of the tree must be such 
that each edge connects two different sides.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
long long n, m, l, du[1000007], T, b[1000007], a1, a2, ans, fa[1000007], ss,
    jc[1000007];
const long long k = 1e9 + 7;
int main() {
  cin >> T; // Read number of test cases
  for (int u = 1; u <= T; u++) {
    cin >> n >> m; // Read number of houses and bridges
    ans = 1; // Initialize result to 1 (multiplicative identity)
    jc[0] = 1; // Precompute factorials
    ss = 0; // Counter for number of special nodes (nodes with degree > 1 in the context of tree structure)
    for (int i = 1; i <= n; i++)
      jc[i] = jc[i - 1] * i % k; // Compute factorial modulo k
    for (int i = 1; i <= n; i++)
      b[i] = du[i] = 0; // Reset visited and degree arrays
    for (int i = 1; i <= m; i++) {
      scanf("%lld%lld", &a1, &a2); // Read two nodes of a bridge
      du[a1]++; // Increase degree of node 'a1'
      du[a2]++; // Increase degree of node 'a2'
      fa[a1] = a2; // Store mapping for parent-child relationship
      fa[a2] = a1;
    }
    if (m != n - 1) { // A valid configuration requires the graph to be a tree (m = n - 1)
      puts("0"); // If m > n - 1, then it can't be a tree => impossible to arrange
      continue;
    }
    if (n == 2) {
      puts("2"); // Special case for two nodes: either one on each side
      continue;
    }
    for (int i = 1; i <= n; i++)
      if (du[i] == 1)
        b[fa[i]]++; // Count how many leaf nodes are connected to the same node in tree-like structure, used later

    for (int i = 1; i <= n; i++) {
      ans = ans * jc[b[i]] % k; // Multiply result by number of ways to permute internal nodes of each component
      du[i] -= b[i]; // Adjust degree to reflect the effect of children count
      if (du[i] > 2)
        ans = 0; // If any node has degree > 2, then it's not valid for planar embedding under constraint
      if (b[i])
        ++ss; // Increment special counter
    }
    ans = ans * 2 * (ss > 1 ? 2 : 1) % k; // Factor in orientation choices and extra combinations due to structure being a tree
    cout << ans << '\n'; // Print final computed answer modulo 1e9+7
  }
}


// https://github.com/VaHiX/codeForces/