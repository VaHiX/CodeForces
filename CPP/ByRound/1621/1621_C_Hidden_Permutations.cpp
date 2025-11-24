// Problem: CF 1621 C - Hidden Permutations
// https://codeforces.com/contest/1621/problem/C

/*
Algorithm:
This problem involves recovering a hidden permutation p using queries on another permutation q.
The key insight is that q is transformed in each query according to the rule q'[i] = q[p[i]].
By performing queries and tracking the transformation, we can trace the structure of p.

Approach:
1. For each unvisited position i in p, start a traversal:
   - Query q[i] to get the current value at position i.
   - Store this value in p[x] where x is the current position.
   - Move to the next position using the value obtained (x = y).
   - Repeat until a position is revisited (i.e., p[x] is already filled), indicating a cycle in the permutation.
2. Once all cycles are processed, the permutation p is reconstructed.

Time Complexity: O(n), since each element is visited at most once during traversal.
Space Complexity: O(n), to store the permutation p.
*/

#include <stdio.h>

const int N = 1e5 + 3;
int n, p[N];
signed main() {
  int x, y;
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      p[i] = 0;
    for (int i = 1; i <= n; i++)
      if (!p[i]) {  // If this position is not yet processed
        x = 0;     // x tracks the previous position in the cycle
        while (1) {
          printf("? %d\n", i);   // Query q[i]
          fflush(stdout);        // Flush output to ensure query is sent
          scanf("%d", &y);       // Read the returned value
          p[x] = y;              // Assign the value to the previous position
          x = y;                 // Move pointer to the value
          if (p[x])              // If the current position is already filled, we have completed a cycle
            break;
        }
      }
    printf("!");  // Output the result
    for (int i = 1; i <= n; i++)
      printf(" %d", p[i]);
    puts(""), fflush(stdout);  // Print newline and flush output
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/