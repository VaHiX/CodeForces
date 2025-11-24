// Problem: CF 815 A - Karen and Game
// https://codeforces.com/contest/815/problem/A

/*
 * Problem: Karen and Game
 * Purpose: Determine the minimum number of row and column increments to transform a grid of zeros into a given target grid.
 * Algorithm:
 *   - First, check if the grid is valid by ensuring that the difference between columns in each row is consistent.
 *   - Then, calculate row and column increments needed using the differences.
 *   - Adjust the increments to make all values non-negative and minimize total operations.
 * Time Complexity: O(n * m)
 * Space Complexity: O(n + m)
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int n, m, i, j, k, ds;
int g[105][105];     // Input grid
int d1[105], d2[105]; // d1 stores row increments, d2 stores column increments

int main() {
  k = 1;      // Flag for validity check
  ds = 0;     // Minimum value tracker
  d2[1] = 0;  // Initialize first column diff

  scanf("%d%d", &n, &m);
  
  // Read first row and compute differences from first column
  for (j = 1; j <= m; j++) {
    scanf("%d", &g[1][j]);
    d2[j] = g[1][j] - g[1][1];  // Store difference from first column
    if (d2[j] < ds)
      ds = d2[j];  // Track minimum difference
  }
  
  // Check consistency across rows
  for (i = 2; i <= n; i++)
    for (j = 1; j <= m; j++) {
      scanf("%d", &g[i][j]);
      if (k && (d2[j] != g[i][j] - g[i][1]))  // Check if differences are consistent
        k = 0;
    }
    
  // If grid is invalid
  if (!k) {
    printf("-1\n");
    return 0;
  }

  // Adjust column differences to ensure non-negative values
  for (j = 1; j <= m; j++)
    d2[j] -= ds;
    
  ds = 1000;
  
  // Calculate row increments
  for (i = 1; i <= n; i++) {
    d1[i] = g[i][1] - d2[1];  // Row increment from first column
    if (d1[i] < ds)
      ds = d1[i];  // Track minimum row increment
  }
  
  // Optimize adjustments for total number of operations
  if (n > m) {
    for (i = 1; i <= n; i++)
      d1[i] -= ds;
    for (j = 1; j <= m; j++)
      d2[j] += ds;
  }
  
  k = 0;
  
  // Calculate total operations
  for (i = 1; i <= n; i++)
    k += d1[i];
  for (j = 1; j <= m; j++)
    k += d2[j];
    
  printf("%d\n", k);
  
  // Print row operations
  for (i = 1; i <= n; i++)
    for (j = 1; j <= d1[i]; j++)
      printf("row %d\n", i);
      
  // Print column operations
  for (j = 1; j <= m; j++)
    for (i = 1; i <= d2[j]; i++)
      printf("col %d\n", j);
      
  return 0;
}


// https://github.com/VaHiX/CodeForces/