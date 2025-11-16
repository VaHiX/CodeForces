// Problem: CF 1801 A - The Very Beautiful Blanket
// https://codeforces.com/contest/1801/problem/A

/*
Code Purpose:
This program generates a beautiful blanket matrix B of size n x m, where each 4x4 submatrix satisfies specific XOR conditions.
The strategy is to assign values such that the XOR of opposite corners in each 4x4 block is equal,
and to maximize the number of distinct values used in the matrix.

Algorithms/Techniques:
- Uses a simple pattern-based approach to construct the matrix.
- Each element B[i][j] is assigned the value (i << 9) + j, which ensures that:
    * Different rows and columns result in different values.
    * The conditions for beautiful blanket are satisfied due to the specific structure and properties of XOR.
- This method allows every element to be unique, thus achieving maximum number of different numbers (n * m).

Time Complexity: O(n * m)
Space Complexity: O(1) excluding output storage

*/

#include <cstdio>
int t, n, m;
signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d %d", &n, &m);
    printf("%d\n", n * m);
    for (int i = 1; i <= n; i++, puts(""))
      for (int j = 1; j <= m; j++)
        printf("%d ", (i << 9) + (j));  // Assign value based on row and column indices to ensure uniqueness and satisfy the constraints
  }
}


// https://github.com/VaHiX/CodeForces/