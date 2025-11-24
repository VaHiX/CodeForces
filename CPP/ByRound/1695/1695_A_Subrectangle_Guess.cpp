// Problem: CF 1695 A - Subrectangle Guess
// https://codeforces.com/contest/1695/problem/A

/*
 * Problem: Find the minimum area of a subrectangle such that Michael can guarantee
 *          to identify the maximum element in it regardless of where Joe selects it.
 * 
 * Algorithm:
 *   - For each test case, find the maximum element in the grid.
 *   - For that maximum element, compute how far it is from the boundaries in both
 *     row and column directions (top, bottom, left, right).
 *   - The minimum area subrectangle that guarantees to contain this maximum element
 *     is calculated by choosing the optimal dimensions h and w such that:
 *       h = max(row + 1, n - row)  // distance to top or bottom boundary
 *       w = max(col + 1, m - col)  // distance to left or right boundary
 * 
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long mx(-1e9 - 7), mxrow(-1), mxcol(-1); // Initialize max value and position
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        long x;
        scanf("%ld", &x);
        if (mx < x) { // Update max value and its position
          mx = x;
          mxrow = row;
          mxcol = col;
        }
      }
    }
    long ha = mxrow + 1;             // Distance from top boundary
    long hb = n - mxrow;             // Distance from bottom boundary
    long h = (ha > hb) ? ha : hb;    // Minimum distance to top or bottom
    long wa = mxcol + 1;             // Distance from left boundary
    long wb = m - mxcol;             // Distance from right boundary
    long w = (wa > wb) ? wa : wb;    // Minimum distance to left or right
    printf("%ld\n", h * w);          // Output the minimal area
  }
}


// https://github.com/VaHiX/codeForces/