// Problem: CF 641 B - Little Artem and Matrix
// https://codeforces.com/contest/641/problem/B

/*
 * Code Purpose: This program reconstructs an initial matrix that is consistent with a series of operations
 * performed on a matrix. The operations include cyclic shifts of rows and columns, and queries about 
 * specific cell values at certain time steps.
 *
 * Algorithm: 
 * 1. Parse all operations and store them in order.
 * 2. Process the operations in reverse order to reconstruct the initial matrix:
 *    - For queries (type 3), directly assign the value to the corresponding cell.
 *    - For row shifts (type 1), reverse the shift operation.
 *    - For column shifts (type 2), reverse the shift operation.
 * 3. Output the reconstructed matrix.
 *
 * Time Complexity: O(q * (n + m)), where q is number of operations, n is number of rows, m is number of columns.
 * Space Complexity: O(q * 4 + n * m), for storing operations and the matrix.
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m, q;
  scanf("%ld %ld %ld\n", &n, &m, &q);
  std::vector<std::vector<long>> op(q, std::vector<long>(4, 0));
  for (long p = 0; p < q; p++) {
    long x;
    scanf("%ld ", &x);
    op[p][0] = x;
    if (x < 3) {
      long y;
      scanf("%ld\n", &y);
      op[p][1] = y - 1;
    } else {
      long y, z, w;
      scanf("%ld %ld %ld\n", &y, &z, &w);
      op[p][1] = y - 1;
      op[p][2] = z - 1;
      op[p][3] = w;
    }
  }
  std::vector<std::vector<long>> data(n, std::vector<long>(m, 0));
  for (long p = q - 1; p >= 0; p--) {
    std::vector<long> exp = op[p];
    if (exp[0] == 1) {
      // Reverse the row shift (left shift -> right shift)
      long row = exp[1];
      long temp = data[row][m - 1];  // Store last element
      for (int col = m - 1; col > 0; col--) {
        data[row][col] = data[row][col - 1];  // Shift elements right
      }
      data[row][0] = temp;  // Place last element at first
    } else if (exp[0] == 2) {
      // Reverse the column shift (up shift -> down shift)
      long col = exp[1];
      long temp = data[n - 1][col];  // Store last element
      for (int row = n - 1; row > 0; row--) {
        data[row][col] = data[row - 1][col];  // Shift elements down
      }
      data[0][col] = temp;  // Place last element at first
    } else if (exp[0] == 3) {
      // Direct assignment for querying cell values
      long row(exp[1]), col(exp[2]), value(exp[3]);
      data[row][col] = value;
    }
  }
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      printf("%ld ", data[row][col]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/