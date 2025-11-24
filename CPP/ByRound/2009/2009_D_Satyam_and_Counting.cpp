// Problem: CF 2009 D - Satyam and Counting
// https://codeforces.com/contest/2009/problem/D

/*
 * Problem:Satyam and Counting
 * Algorithm: Counting right triangles using coordinate compression and pattern matching.
 * 
 * Approach:
 * - Points are placed on two horizontal lines y=0 and y=1.
 * - For each point (x, 0), we check how many points exist at (x, 1) and count combinations.
 * - Additionally, we check for valid right triangles where:
 *   - One leg is horizontal (y=0 or y=1) and the other vertical.
 *   - A right triangle can be formed by three points: two on same y, one on different y.
 * 
 * Time Complexity: O(n), where n is number of points.
 * Space Complexity: O(n), to store the presence of points on two rows.
 */
#include <stdio.h>
typedef long long LL;
char a[2][200002];  // a[0] represents y=0 row, a[1] represents y=1 row
int main() {
  int T, n, x, y, i, t;
  LL ans;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    // Initialize the grid
    for (i = 0; i <= n; i++) {
      a[0][i] = a[1][i] = 0;
    }
    // Mark presence of points
    for (i = 0; i < n; i++) {
      scanf("%d%d", &x, &y);
      a[y][x] = 1;
    }
    // Count triangles where both points are on same x coordinate but different y
    for (i = 0, ans = 0, t = n - 2; i <= n; i++) {
      if (a[0][i] == 1 && a[1][i] == 1)
        ans += t;  // Add number of points not at current x
    }
    // Handle edge cases for triangles with legs of different directions
    // Check for triangles with horizontal and vertical legs
    for (i = 1; i < n; i++) {
      if (a[0][i] == 1 && a[1][i - 1] == 1 && a[1][i + 1] == 1)
        ans++;  // Case: (i,0) and (i-1,1) (i+1,1) form a triangle
      if (a[1][i] == 1 && a[0][i - 1] == 1 && a[0][i + 1] == 1)
        ans++;  // Case: (i,1) and (i-1,0) (i+1,0) form a triangle
    }
    printf("%lld\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/