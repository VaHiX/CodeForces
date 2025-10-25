// Problem: CF 1231 C - Increasing Matrix
// https://codeforces.com/contest/1231/problem/C

/*
C. Increasing Matrix
Task: Given an n x m matrix with some zeros, replace each zero with a positive integer such that:
- Each row strictly increases from left to right
- Each column strictly increases from top to bottom
- The sum of all elements is maximized
Return the maximum possible sum or -1 if impossible.

Approach:
1. First, process from bottom-right to top-left (reverse traversal).
   For each 0, compute its value based on neighbors (min of right and down).
   Ensure it's greater than both the cell below and to the right.
2. Then verify that all conditions are met for increasing rows/columns.
3. Calculate total sum.

Time Complexity: O(n * m)
Space Complexity: O(n * m)

Algorithms/Techniques:
- Greedy approach with backward traversal
- Validation step after assignment
*/

#include <cstdio>
#include <vector>
int main() {
  long nrow, ncol;
  scanf("%ld %ld", &nrow, &ncol);
  std::vector<std::vector<long>> a(nrow, std::vector<long>(ncol, 0));
  for (long row = 0; row < nrow; row++) {
    for (long col = 0; col < ncol; col++) {
      scanf("%ld", &a[row][col]);
    }
  }
  bool possible(true);
  long long sum(0);
  for (long row = nrow - 1; row >= 0 && possible; row--) {
    for (long col = ncol - 1; col >= 0 && possible; col--) {
      if (a[row][col]) {
        sum += a[row][col];
        continue;
      }
      // Compute minimum of adjacent cells and subtract one to make it valid
      long x = (a[row + 1][col] < a[row][col + 1] ? a[row + 1][col]
                                                  : a[row][col + 1]) -
               1;
      // If new value isn't greater than neighbors above and left, impossible
      if (x <= a[row - 1][col] || x <= a[row][col - 1]) {
        possible = false;
        break;
      } else {
        a[row][col] = x;
        sum += x;
      }
    }
  }
  // Validate the matrix is increasing in both directions
  for (long row = 0; row < nrow && possible; row++) {
    for (long col = 0; col < ncol && possible; col++) {
      // Check upwards and downwards neighbors
      if (row > 0 && a[row][col] <= a[row - 1][col]) {
        possible = false;
      }
      if (row + 1 < nrow && a[row][col] >= a[row + 1][col]) {
        possible = false;
      }
      // Check left and right neighbors
      if (col > 0 && a[row][col] <= a[row][col - 1]) {
        possible = false;
      }
      if (col + 1 < ncol && a[row][col] >= a[row][col + 1]) {
        possible = false;
      }
    }
  }
  if (possible) {
    printf("%lld\n", sum);
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/