// Problem: CF 2000 F - Color Rows and Columns
// https://codeforces.com/contest/2000/problem/F

/*
F. Color Rows and Columns
time limit per test3 seconds
memory limit per test256 megabytes

Task:
You have n rectangles, the i-th of which has a width of a_i and a height of b_i.
You can perform the following operation: choose a rectangle and a cell in it, and then color it.
Each time you completely color any row or column, you earn 1 point.
Your task is to score at least k points with as few operations as possible.

Algorithms/Techniques:
- Dynamic Programming on rectangles
- For each rectangle, precompute the cost of coloring rows/columns in a greedy manner
- Use DP state: d[i][j] = minimum operations to achieve exactly j points using first i rectangles

Time Complexity: O(n * k * (a_max + b_max)) where a_max, b_max are up to 100
Space Complexity: O(n * k) for the DP table

*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
int t, n, k, a[1005], b[1005], d[1005][105];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &k);
    memset(d, 63, sizeof d); // Initialize DP table with large values
    d[0][0] = 0; // Base case: 0 points with 0 rectangles requires 0 operations

    for (int i = 1; i <= n; i++) {
      scanf("%d%d", a + i, b + i);
      // For current rectangle, compute cost for all possible point values
      for (int x = a[i], y = b[i], r = 0, s = 0; s <= min(a[i] + b[i], k); s++) {
        // For each number of points s we want to achieve from this rectangle
        for (int j = s; j <= k; j++)
          d[i][j] = min(d[i][j], d[i - 1][j - s] + r); // Update DP state

        // Greedily decide whether to color a row or column next:
        // Prefer the dimension with smaller size
        if (x < y) {
          r += x; // Add cost of coloring one more row (width)
          y--;    // Decrease height available for coloring
        } else {
          r += y; // Add cost of coloring one more column (height)
          x--;    // Decrease width available for coloring
        }
      }
    }
    printf("%d\n", d[n][k] >= 4144959 ? -1 : d[n][k]); // Output result or -1 if impossible
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/