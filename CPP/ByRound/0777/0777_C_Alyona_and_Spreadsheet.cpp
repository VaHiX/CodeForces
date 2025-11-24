// Problem: CF 777 C - Alyona and Spreadsheet
// https://codeforces.com/contest/777/problem/C

/*
 * Problem: Alyona and Spreadsheet
 * Purpose: Determine if any column in a given range of rows is sorted in non-decreasing order.
 * 
 * Algorithm:
 * 1. For each column, precompute the earliest row where a violation occurs in the column.
 * 2. For each query (l, r), check if there exists a column where all rows from l to r are sorted.
 *    This is true if the earliest violation in that column is before the start of the query range.
 * 
 * Time Complexity: O(n * m + k)
 * Space Complexity: O(n + m)
 * 
 * Techniques:
 * - Preprocessing to track violation points per column
 * - Range query optimization using precomputed arrays
 */

#include <cstdio>
#include <vector>
int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<long> a(m, 0), b(m, 0), c(n, 0);
  for (long row = 0; row < n; row++) {
    c[row] = row; // Initialize c[row] to the row index
    for (long col = 0; col < m; col++) {
      long x;
      scanf("%ld", &x);
      if (x < a[col]) { // If current element is less than previous in same column
        b[col] = row;  // Mark the row where violation occurs
      }
      a[col] = x; // Update the previous value in column
      if (b[col] < c[row]) { // If violation in column happens earlier than current row
        c[row] = b[col]; // Update earliest violation row for current row
      }
    }
  }
  long k;
  scanf("%ld", &k);
  while (k--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    --l;  // Convert to 0-based indexing
    --r;  // Convert to 0-based indexing
    puts((c[r] <= l) ? "Yes" : "No"); // If earliest violation is before l, the range is sorted
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/