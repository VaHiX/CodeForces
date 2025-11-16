// Problem: CF 913 B - Christmas Spruce
// https://codeforces.com/contest/913/problem/B

/*
 * Problem: Christmas Spruce
 * Purpose: Determine if a given rooted tree is a "spruce", i.e., every non-leaf node has at least 3 leaf children.
 * Algorithm:
 *   1. Build an adjacency list representation of the tree from parent information.
 *   2. For each node, count how many of its children are leaves (have no children themselves).
 *   3. If any non-leaf node has fewer than 3 leaf children, the tree is not a spruce.
 *
 * Time Complexity: O(n), where n is the number of nodes. We traverse each node once to build the tree and once to check conditions.
 * Space Complexity: O(n), for storing the adjacency list and the tree structure.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<std::vector<long>> g(n + 1); // Adjacency list to represent the tree
  for (long p = 2; p <= n; p++) { // Read parent of each node from 2 to n
    long x;
    scanf("%ld", &x);
    g[x].push_back(p); // Add child to parent's list
  }
  bool spruce(true); // Assume the tree is a spruce initially
  for (long p = 1; p <= n; p++) { // Check each node
    if (g[p].size() == 0) {
      continue; // Skip leaf nodes since they can't be non-leaf
    }
    long cnt(0); // Count of leaf children for current node
    for (long u = 0; u < g[p].size(); u++) {
      cnt += (g[g[p][u]].size() == 0); // Increment if child node is a leaf (no children)
    }
    if (cnt < 3) {
      spruce = false; // Not a spruce if less than 3 leaf children
      break;
    }
  }
  puts(spruce ? "Yes" : "No"); // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/