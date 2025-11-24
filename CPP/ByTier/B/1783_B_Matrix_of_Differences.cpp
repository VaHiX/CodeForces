// Problem: CF 1783 B - Matrix of Differences
// https://codeforces.com/contest/1783/problem/B

/*
 * Purpose: This code constructs a square matrix of size n×n filled with integers from 1 to n²
 * such that the "beauty" of the matrix (the number of distinct absolute differences between 
 * adjacent elements) is maximized.
 * 
 * Algorithm/Technique: 
 * - The algorithm uses a zigzag filling pattern:
 *   - For each row, fill from left to right, alternating between:
 *     - Increasing from the smallest available number (left++), or
 *     - Decreasing from the largest available number (right--)
 *   - After filling each row, if the row index is odd, reverse the row to create a zigzag pattern.
 * - This approach ensures that adjacent elements in the resulting matrix have a wide range of 
 *   absolute differences, maximizing the number of distinct values.
 * 
 * Time Complexity: O(n²) - We iterate through all n×n cells once to fill the matrix.
 * Space Complexity: O(n²) - The matrix itself stores n² integers.
 */

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::vector<long>> a(n, std::vector<long>(n));
    long left(1), right(n * n);  // left starts at 1, right starts at n²
    bool flag(0);                // flag determines whether to use left or right value
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        if (flag) {
          a[row][col] = left++;    // assign from left and increment left
        } else {
          a[row][col] = right--;   // assign from right and decrement right
        }
        flag ^= 1;                 // toggle the flag for next cell
      }
      if (row & 1)                 // if row index is odd
        reverse(a[row].begin(), a[row].end());  // reverse the row for zigzag pattern
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < n; col++) {
        printf("%ld ", a[row][col]);
      };
      puts("");
    }
  }
}


// https://github.com/VaHiX/CodeForces/