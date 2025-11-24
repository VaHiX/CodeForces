// Problem: CF 959 C - Mahmoud and Ehab and the wrong algorithm
// https://codeforces.com/contest/959/problem/C

/*
 * Code Purpose: 
 * This program generates two trees with n nodes to demonstrate the incorrectness 
 * of Mahmoud's algorithm for the vertex cover problem on trees.
 * 
 * Algorithm:
 * - For the first tree (incorrect answer case): 
 *   - Creates a star-like structure rooted at node 1 with 3 initial branches.
 *   - Then adds remaining nodes in a way that creates a pattern where 
 *     the algorithm picks more vertices than optimal.
 * - For the second tree (correct answer case):
 *   - Simply generates a star (all nodes connected to node 1).
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1) (excluding output)
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  if (n < 6) {
    // For n < 6, it's impossible to construct the required trees
    puts("-1");
  } else {
    // First tree: Construct a tree where the algorithm gives wrong answer
    // Start with a central node 1 connected to nodes 2, 3, 4
    printf("1 2\n1 3\n1 4\n2 5\n2 6\n");
    // Then connect the rest in a pattern that causes the algorithm to overestimate
    for (long p = 7; p <= n; p++) {
      // Alternate connection with 1 and 2 to make depth pattern incorrect
      printf("%d %ld\n", (p % 2 ? 1 : 2), p);
    }
  }
  // Second tree: A simple star (rooted at 1, all other nodes connected to it)
  // This tree is used to verify the algorithm works correctly on this structure
  for (long p = 2; p <= n; p++) {
    printf("1 %ld\n", p);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/