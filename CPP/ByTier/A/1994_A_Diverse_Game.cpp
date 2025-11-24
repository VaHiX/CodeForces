// Problem: CF 1994 A - Diverse Game
// https://codeforces.com/contest/1994/problem/A

/*
 * Code Purpose:
 * This solution constructs a new matrix 'b' from the given matrix 'a' such that
 * no element in 'b' is the same as the corresponding element in 'a'.
 * The approach involves performing a series of swaps to rearrange elements,
 * ensuring all positions are different.
 *
 * Algorithm:
 * 1. For each test case, we attempt to construct matrix 'b' by swapping elements.
 * 2. First, we swap adjacent elements in the first row to shift values.
 * 3. Then, we perform row-wise swaps to further rearrange the matrix.
 * 4. If the matrix size is 1x1, it's impossible to satisfy the requirement, so return -1.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for storing the matrix
 */
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> a(n, std::vector<long>(m, 0));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &a[row][col]);
      }
    }
    // Swap adjacent elements in the first row to shuffle the elements
    for (long col = 0; col + 1 < m; col++) {
      long tmp = a[0][col];
      a[0][col] = a[0][col + 1];
      a[0][col + 1] = tmp;
    }
    // Swap rows to further shuffle the matrix
    for (long row = 0; row + 1 < n; row++) {
      std::vector<long> tmp = a[row];
      a[row] = a[row + 1];
      a[row + 1] = tmp;
    }
    // Special case: if the matrix is 1x1, it's impossible to have a different element
    if (n * m == 1) {
      puts("-1");
      continue;
    }
    // Output the constructed matrix
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        printf("%ld ", a[row][col]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/