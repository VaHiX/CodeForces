// Problem: CF 2094 C - Brr Brrr Patapim
// https://codeforces.com/contest/2094/problem/C

/* 
C. Brr Brrr Patapim
Problem: Given an n x n grid where G[i][j] = p[i+j], reconstruct the permutation p of 2*n elements.
Algorithm: 
  - Use the fact that elements on the same diagonal (i + j = constant) are all part of the permutation.
  - Mark which numbers appear in the grid as used.
  - Find the unused number to assign to p[1] (since p[1] must be at position (1,1) where i+j=2, but we have p[1]), and then deduce other elements in order from diagonal sums.

Time Complexity: O(n^2) per test case.
Space Complexity: O(n) for vectors of size 2*n+1 (for indexing from 1).

Techniques:
- Use of diagonals to determine permutation elements
- Boolean array for marking used elements
- Vector storage and retrieval based on diagonal sum index
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(2 * n + 1, 0);       // Vector to store the permutation p[1..2*n]
    std::vector<bool> w(2 * n + 1, 1);       // Boolean vector to track which numbers are present in grid
    for (long row = 1; row <= n; row++) {
      for (long col = 1; col <= n; col++) {
        long x;
        scanf("%ld", &x);
        w[x] = 0;                             // Mark the number as used
        v[row + col] = x;                     // Store in diagonal index
      }
    }
    for (long p = 1; p <= 2 * n; p++) {
      if (w[p]) {                             // Find unused number to place at p[1]
        v[1] = p;
        break;
      }
    }
    for (long p = 1; p <= 2 * n; p++) {
      printf("%ld ", v[p]);                   // Output the reconstructed permutation
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/