// Problem: CF 1893 A - Anonymous Informant
// https://codeforces.com/contest/1893/problem/A

/*
Problem: Anonymous Informant
Algorithm: Simulation with cycle detection and modular arithmetic
Time Complexity: O(n) amortized per test case
Space Complexity: O(n)

This problem involves checking whether a given array b can be obtained by performing
k operations on an unknown array a, where each operation selects a fixed point x,
and cyclically shifts the array left by x positions.

The solution simulates the process in reverse: starting from the final array b,
we try to trace back to the original array by reversing the operations. 
We attempt up to min(n, k) steps and check whether we can return to a valid position.
*/
#include <stdio.h>
#include <algorithm>

using namespace std;
int T, a[1000005];
int main() {
  scanf("%d", &T);
  while (T--) {
    int n, m, fl = 1;
    scanf("%d%d", &n, &m); // Read n and k
    m = min(n, m);        // Limit the number of operations to n for efficiency
    int kk = n;           // Start from the last index of the array
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]); // Read the elements into array a (1-indexed)
    for (int i = 1; i <= m; i++) {
      // Check if current value at position kk is a valid index within [1, n]
      fl &= (a[kk] <= n);
      // Perform reverse operation: move back kk positions
      kk -= a[kk];
      // Handle wrapping around using modular arithmetic (simulate cyclic shift)
      if (kk < 1) {
        kk %= n;
        kk += n; // Ensure kk remains positive
      }
    }
    printf(fl ? "Yes\n" : "No\n"); // Print result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/