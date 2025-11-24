// Problem: CF 2118 B - Make It Permutation
// https://codeforces.com/contest/2118/problem/B

/*
B. Make It Permutation
Algorithm: Greedy construction with row reversal operations.
Approach:
- For each row i from 1 to n-1, reverse the subarray from column p to n such that
  the value at position (i, p) becomes the last element of row i after reversal.
- Then reverse the last row to get the final permutation.
Time Complexity: O(n^2) - due to nested loop and operations on each row.
Space Complexity: O(1) - only using a fixed amount of extra variables.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", 2 * n - 1); // Total operations needed
    for (long p = 1; p < n; p++) {
      // Reverse subarray in row p from column p to n
      printf("%ld 1 %ld\n%ld %ld %ld\n", p, p, p, p + 1, n);
    }
    // Reverse entire last row
    printf("%ld 1 %ld\n", n, n);
  }
}


// https://github.com/VaHiX/codeForces/