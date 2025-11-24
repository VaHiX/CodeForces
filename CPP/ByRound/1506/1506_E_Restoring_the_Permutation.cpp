// Problem: CF 1506 E - Restoring the Permutation
// https://codeforces.com/contest/1506/problem/E

/*
E. Restoring the Permutation
Algorithms/Techniques: Greedy, Stack Simulation

Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This solution reconstructs lexicographically minimal and maximal permutations 
from a given array q where q[i] = max(p[1], ..., p[i]) for original permutation p.
The approach uses two passes:
1. First pass builds the minimal permutation by greedily placing smallest available numbers.
2. Second pass uses a stack to simulate backtracking for maximizing the permutation.

*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 2e5 + 7;
int n, top, a[N], st[N];
bool b[N];

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), b[i] = 0; // Read input and reset boolean array
    
    int p = 1; // Pointer to find next smallest available number
    for (int i = 1; i <= n; i++)
      if (a[i] != a[i - 1]) { // If current max changes from previous
        b[a[i]] = 1; // Mark this number as used
        printf("%d ", a[i]); // Output the actual value
      } else { // If current value is same as previous max, we must place a smaller unused number
        while (b[p]) // Find next unused number
          ++p;
        b[p] = 1; // Mark it used
        printf("%d ", p); // Output this number
      }
    puts(""); // End of line for first result
    
    top = 0; // Reset stack pointer
    for (int i = 1; i <= n; i++)
      if (a[i] != a[i - 1]) { // If value increased
        printf("%d ", a[i]); // Output original number
        // Push all intermediate numbers into stack
        for (int j = a[i - 1] + 1; j < a[i]; j++)
          st[++top] = j;
      } else // If value same as before, pop from stack to get max permutation
        printf("%d ", st[top--]);
    puts(""); // End of line for second result
  }
}


// https://github.com/VaHiX/codeForces/