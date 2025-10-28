// Problem: CF 1950 F - 0, 1, 2, Tree!
// https://codeforces.com/contest/1950/problem/F

/*
 * Problem: Find the minimum height of a rooted tree with specified numbers of vertices
 *          having 0, 1, or 2 children.
 *
 * Algorithms/Techniques:
 *   - Greedy approach to simulate tree construction
 *   - Maintain current level size and next level size to calculate height
 *
 * Time Complexity: O(1) per test case (since we only iterate a+b times, which is bounded)
 * Space Complexity: O(1) - only using a few variables
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    // Check if the tree is valid: c must be equal to a + 1 for a valid tree
    if (c != a + 1) {
      puts("-1");
      continue;
    }
    // Special case: if there are no internal nodes, height is 0
    if (!a && !b) {
      puts("0");
      continue;
    }
    // Simulate building the tree level by level
    long cur(1), nxt(0), depth(1); // cur: nodes in current level, nxt: nodes in next level, depth: current depth
    for (long p = 0; p < a + b; p++) {
      // If no nodes left in current level, move to next level
      if (!cur) {
        cur = nxt;
        nxt = 0;
        ++depth;
      }
      --cur; // consume one node from current level
      // Add children for this node (2 children if it's an 'a' node, 1 otherwise)
      nxt += 1 + (p < a);
    }
    printf("%ld\n", depth);
  }
}


// https://github.com/VaHiX/CodeForces/