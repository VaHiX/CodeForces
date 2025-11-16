// Problem: CF 1162 B - Double Matrix
// https://codeforces.com/contest/1162/problem/B

/*
B. Double Matrix
Algorithms/Techniques: Greedy, Sorting, Matrix manipulation

Time Complexity: O(n * m * log(n * m))
Space Complexity: O(n * m)

The problem involves two n×m matrices and the goal is to make both matrices strictly increasing 
(row-wise and column-wise) by swapping elements at corresponding positions between the matrices.

Approach:
1. Read input matrices a and b.
2. For each position (i,j), we can choose either a[i][j] or b[i][j] for our final matrix.
3. To ensure both matrices are increasing, we need to greedily select smaller values from a and larger from b,
   but only such that the resulting sequences are strictly increasing rows/columns.
4. After processing, check if the final arrangement of both matrices satisfies strictly increasing property
   for rows and columns.

This approach uses greedy selection followed by verification of increasing properties across both matrices.
*/

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::vector<long>> a(n, std::vector<long>(m, 0)),
      b(n, std::vector<long>(m, 0));
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      scanf("%ld", &a[row][col]);
    }
  }
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      scanf("%ld", &b[row][col]);
    }
  }
  // Greedily assign smaller element to 'a' and larger to 'b'
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      long x(a[row][col]), y(b[row][col]);
      a[row][col] = (x < y) ? x : y;
      b[row][col] = (x > y) ? x : y;
    }
  }
  bool possible(true);
  // Check if both matrices satisfy strictly increasing property
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      if ((row > 0 && a[row][col] <= a[row - 1][col]) ||
          (col > 0 && a[row][col] <= a[row][col - 1])) {
        possible = false;
      }
      if ((row > 0 && b[row][col] <= b[row - 1][col]) ||
          (col > 0 && b[row][col] <= b[row][col - 1])) {
        possible = false;
      }
    }
  }
  puts(possible ? "Possible" : "Impossible");
  return 0;
}


// https://github.com/VaHiX/codeForces/