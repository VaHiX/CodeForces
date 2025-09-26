// Problem: CF 2121 C - Those Who Are With Us
// https://codeforces.com/contest/2121/problem/C

/*
C. Those Who Are With Us
Algorithm: Greedy + Simulation
Time Complexity: O(n * m) per test case
Space Complexity: O(n + m) per test case

The problem asks to minimize the maximum value in a matrix after performing exactly one operation,
which decreases all elements in a chosen row and column by 1.

Approach:
1. Find the maximum value in the matrix.
2. Count how many times each row and column appears in cells with the maximum value.
3. For each cell (i,j), check if changing that cell's row and column leads to eliminating the maximum,
   i.e., the total number of "max" elements that will be reduced is such that it makes a single
   element become the new minimal possible max.

Key observations:
- For any valid operation (row r, column c), all cells in row r or column c decrease by 1.
- If an element equals the current max, increasing its count in vr[row] and vc[col] indicates
  this row/column contributes to a maximum element.
- We iterate over all cells to see if we can reduce the maximum by making one cell equal to mx - 1,
  i.e., if that single operation causes a valid reduction in the final result.
*/

#include <cstdio>
#include <vector>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> f(n, std::vector<long>(m, 0));
    long mx(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &f[row][col]);
        mx = (mx > f[row][col] ? mx : f[row][col]); // Update maximum value
      }
    }
    std::vector<long> vr(n), vc(m); // Count of max elements in each row/column
    long mxcnt(0); // Total count of cells with max value
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        if (f[row][col] < mx) {
          continue; // Skip non-max elements
        }
        ++vr[row];     // Increment row count
        ++vc[col];     // Increment column count
        ++mxcnt;       // Increment total max element count
      }
    }
    bool single(false); // Flag to determine if a single max cell can reduce the final max to mx - 1
    for (long row = 0; !single && row < n; row++) {
      for (long col = 0; !single && col < m; col++) {
        // Check if changing this entire row and column leads to the reduction of max
        single |= ((vr[row] + vc[col] - (f[row][col] == mx)) == mxcnt);
      }
    }
    printf("%ld\n", mx - single); // Output result: original max minus 1 if single cell can reduce it
  }
}


// https://github.com/VaHiX/codeForces/