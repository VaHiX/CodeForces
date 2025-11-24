// Problem: CF 1583 B - Omkar and Heavenly Tree
// https://codeforces.com/contest/1583/problem/B

/*
 * Code Purpose: This program constructs a tree with n nodes that satisfies
 *               given m restrictions. Each restriction specifies that a certain
 *               node b must not lie on the simple path between nodes a and c.
 *               The solution works by:
 *               1. Identifying a "central" node that is not forbidden by any
 *                  restriction (by removing all forbidden nodes from a set of all nodes).
 *               2. Connecting this central node to all other nodes.
 *               This ensures no forbidden node lies on any path between two other nodes.
 *
 * Algorithms/Techniques: Set operations to eliminate forbidden nodes and
 *                        tree construction using a central node.
 *
 * Time Complexity: O(n + m) per test case, where n is the number of nodes and m is the number of restrictions.
 *                  Insertion and deletion in set is O(log n), but since we do it a fixed number of times,
 *                  we can consider it as O(n + m) overall.
 *
 * Space Complexity: O(n) for storing the set of nodes and the result edges.
 */

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::set<long> s;
    for (long p = 1; p <= n; p++) {
      s.insert(p);  // Initialize set with all nodes from 1 to n
    }
    for (long p = 0; p < m; p++) {
      long a, b, c;
      scanf("%ld %ld %ld", &a, &b, &c);
      s.erase(b);  // Remove the forbidden node b from the set
    }
    long cnode = *s.begin();  // Pick the first node from the remaining set as central node
    for (long p = 1; p <= n; p++) {
      if (p == cnode) {
        continue;  // Skip the central node to avoid self-loop
      }
      printf("%ld %ld\n", cnode, p);  // Connect central node to all other nodes
    }
  }
}


// https://github.com/VaHiX/CodeForces/