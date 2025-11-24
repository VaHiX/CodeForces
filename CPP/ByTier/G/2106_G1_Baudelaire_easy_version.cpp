// Problem: CF 2106 G1 - Baudelaire (easy version)
// https://codeforces.com/contest/2106/problem/G1

#include <cstdio>
// Problem: Interactive tree node value reconstruction using two query types
// Algorithm: Use prefix sums and toggling to deduce values
// Time Complexity: O(n) per test case (at most 2*n+200 queries)
// Space Complexity: O(n) for storing node values

int ans[1005]; // Store the computed values of nodes

int main() {
  int t, n, u, v, p; // t = number of test cases, n = tree size
  scanf("%d", &t); // Read number of test cases
  while (t--) { // Process each test case
    scanf("%d", &n); // Read size of the tree
    for (int i = 0; i < n - 1; i++) // Read edges (but not used in this logic)
      scanf("%d%d", &u, &v);
    
    // Query sum of prefix values from root to nodes 1,2,...,n
    printf("? 1 1 1\n"); // Ask for f(1) by querying path to node 1
    fflush(stdout); // Flush output buffer
    scanf("%d", &ans[1]); // Read the result
    
    if (ans[1] & 1) { // If f(1) is odd
      // Process all nodes using the fact that f(i) - f(1) = value of node i
      for (int i = 2; i <= n; i++) {
        printf("? 1 1 %d\n", i); // Query f(i)
        fflush(stdout);
        scanf("%d", &ans[i]); // Read the result
        ans[i] -= ans[1]; // Compute difference, which is value of node i
      }
    } else { // If f(1) is even
      // We may have issues with parity, so we toggle and re-query
      if (ans[1]) {
        printf("? 2 1\n"); // Toggle value of root to distinguish it from other nodes
        fflush(stdout);
      }

      // Query all f(i) for i=2 to n
      for (int i = 2; i <= n; i++) {
        printf("? 1 1 %d\n", i); // Query f(i)
        fflush(stdout);
        scanf("%d", &ans[i]); // Read the result
      }

      // Re-query to determine the root
      printf("? 2 1\n"); // Toggle value of node 1 again
      fflush(stdout);
      
      printf("? 1 1 1\n"); // Query f(1) to get correct parity information
      fflush(stdout);
      scanf("%d", &ans[1]); 

      ans[1] /= 2; // Halve because we're working with root adjustments
    }
    
    // Output final answer
    printf("!");
    for (int i = 1; i <= n; i++)
      printf(" %d", ans[i]);
    printf("\n");
    fflush(stdout);
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/