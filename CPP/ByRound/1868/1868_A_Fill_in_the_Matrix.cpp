// Problem: CF 1868 A - Fill in the Matrix
// https://codeforces.com/contest/1868/problem/A

/*
Code Purpose:
This program fills an n x m matrix such that the beauty of the matrix (defined as the MEX of column values) is maximized.
Each row is a permutation of integers from 0 to m-1.
The algorithm uses a cyclic shifting technique to construct rows that distribute values evenly across columns,
ensuring high diversity in column MEX values.

Algorithms/Techniques:
- Cyclic shifting of column indices to create permutations
- Mathematically designed row construction to maximize MEX across columns

Time Complexity: O(n * m) - Each element of the matrix is computed once.
Space Complexity: O(1) - Only a constant amount of extra space is used (excluding output storage).
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
int n, m, i, j, T_T;
int main() {
  for (scanf("%d", &T_T); T_T--;) {
    scanf("%d%d", &n, &m);
    // Output the maximum possible beauty of the matrix.
    // If m > 1, maximum beauty is min(n + 1, m), otherwise it's 0.
    printf("%d\n", m > 1 ? min(n + 1, m) : 0);
    // Generate each row of the matrix.
    for (i = 1; i <= n; ++i, puts(""))
      // For each row, compute the value at column j using cyclic shift.
      for (j = 1; j <= m; ++j)
        printf("%d ", (min(i, m - 1) + j) % m);
  }
}


// https://github.com/VaHiX/CodeForces/