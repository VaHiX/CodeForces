// Problem: CF 1188 A1 - Add on a Tree
// https://codeforces.com/contest/1188/problem/A1

/*
 * Problem: A1. Add on a Tree
 * Purpose: Determine whether any configuration of real numbers on edges of a tree
 *          can be achieved using operations that add a value to all edges on a path between two leaves.
 *
 * Algorithm:
 * - The key insight is to check if the tree has any node with degree exactly 2.
 * - If there exists such a node, then it's impossible to achieve certain edge configurations,
 *   because that central node cannot be a leaf and affects paths from leaves in a constrained manner.
 * - We build a degree array of the tree from input edges.
 * - Then we iterate through all nodes and check if any has degree 2.
 *
 * Time Complexity: O(n), where n is the number of nodes.
 * Space Complexity: O(n), for storing the degree array.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> deg(n + 1, 0); // Initialize degree array with zeros
  for (long p = 1; p < n; p++) {   // Read n-1 edges
    long x, y;
    scanf("%ld %ld", &x, &y);
    ++deg[x]; // Increment degree of node x
    ++deg[y]; // Increment degree of node y
  }
  bool possible(true); // Flag to indicate if configuration is possible
  for (long p = 1; p <= n; p++) {   // Check each node's degree
    if (deg[p] == 2) {              // If any node has degree 2, set impossible
      possible = false;
      break;
    }
  }
  puts(possible ? "YES" : "NO");  // Output result
  return 0;
}


// https://github.com/VaHiX/codeForces/