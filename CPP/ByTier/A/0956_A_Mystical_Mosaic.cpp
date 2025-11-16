// Problem: CF 956 A - Mystical Mosaic
// https://codeforces.com/contest/956/problem/A

/*
 * Problem: Mystical Mosaic
 * Purpose: Determine if a given grid of black and white cells can be produced
 *          by a series of operations where each operation selects a subset of
 *          rows and columns to turn their intersections black. Each row/column
 *          can only be used once across all operations.
 *
 * Algorithm:
 *   - Use Union-Find (Disjoint Set Union) to model the constraints:
 *     - Each row is a node in the Union-Find structure.
 *     - Each column is a node in the Union-Find structure.
 *   - For a cell (i,j) to be black, it must be part of an operation that
 *     includes row i and column j.
 *   - If row i and column j are not yet connected in the Union-Find, then
 *     they must be connected to ensure consistent operation selection.
 *   - After processing all black cells:
 *     - For each cell (i,j), check if it was intended to be black.
 *     - If it is black but not correctly connected in the Union-Find,
 *       the configuration is invalid.
 *
 * Time Complexity: O(n * m * α(n + m)), where α is the inverse Ackermann function
 * Space Complexity: O(n + m), for the Union-Find structure and auxiliary arrays
 */

#include <cstdio>
#include <iostream>

#define maxn 105
using namespace std;

int n, m;
bool hv[maxn][maxn]; // hv[i][j] stores whether cell (i, j) is black in input
int fa[maxn];        // Union-Find parent array

// Find root with path compression
int gfa(int a) {
  if (fa[a] == a)
    return a;
  return fa[a] = gfa(fa[a]); // Path compression
}

char inp[maxn];

int main() {
  scanf("%d%d", &n, &m);
  
  // Initialize Union-Find structure
  for (int i = 1; i <= n + m; i++)
    fa[i] = i;

  // Process each row of the input grid
  for (int i = 1; i <= n; i++) {
    scanf("%s", inp);
    for (int j = 0; j < m; j++)
      if (inp[j] == '#') {
        hv[i][j + 1] = 1; // Mark the cell as black
        // Connect row i with column j+1 in Union-Find
        fa[gfa(i)] = gfa(j + n + 1);
      }
  }

  bool flag = 1;
  
  // Check validity of all black cells
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      // If row i and column j are in the same component,
      // but the cell is not marked black, it is an inconsistency
      if (gfa(i) == gfa(j + n))
        if (!hv[i][j])
          flag = 0;

  if (flag)
    printf("Yes\n");
  else
    printf("No\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/