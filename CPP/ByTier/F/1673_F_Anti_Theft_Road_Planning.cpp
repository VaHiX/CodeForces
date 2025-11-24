// Problem: CF 1673 F - Anti-Theft Road Planning
// https://codeforces.com/contest/1673/problem/F

/*
Algorithm: 
This problem is about constructing a grid of roads with specific lengths such that 
the XOR of road lengths along any path can uniquely identify the destination of 
a thief's theft. The key idea is to assign each cell a unique identifier using 
the binary representation of its coordinates, and then use the XOR tracking mechanism 
to reconstruct the path.

The approach involves:
1. Assigning bit patterns to rows and columns such that they form a binary code.
2. Constructing road lengths using powers of 2 based on binary decomposition.
3. Using the XOR of the path to encode row and column information separately.

Time Complexity: O(n^2 + k * log(max_value))
Space Complexity: O(n + k)

The code uses bit manipulation and precomputed binary masks to efficiently 
determine row/column from the XOR values returned by the tracker.
*/

#include <cstdio>
int n, q, x, y, f[33], d;
int main() {
  scanf("%d%d", &n, &q);
  // Initialize the mapping of bit positions to row/column numbers using Fenwick tree logic
  for (int i = 1; i <= n; i++)
    f[x] = i, x ^= i & -i;  // f[x] stores the row/column index for the current bit mask x
  x = 0;  // Reset x to 0 for reuse
  // Output horizontal road lengths
  for (int i = 1; i <= n; i++, puts(""))
    for (int j = 1; j < n; j++)
      printf("%d ", (j & -j) * (j & -j));  // Horizontal edges: use square of lowest set bit
  // Output vertical road lengths
  for (int i = 1; i < n; i++, puts(""))
    for (int j = 1; j <= n; j++)
      printf("%d ", (i & -i) * (i & -i) << 1);  // Vertical edges: double square of lowest set bit
  // Process queries
  while (q--) {
    fflush(stdout);
    scanf("%d", &d);
    // Decompose the XOR result into row and column bits
    for (int i = 0; i <= 9; i++)
      (i & 1 ? x : y) ^= (d >> i & 1) << (i >> 1);  // Separate bits into x (row) and y (col)
    printf("%d %d\n", f[x], f[y]);  // Output row and column of the theft location
  }
}


// https://github.com/VaHiX/CodeForces/