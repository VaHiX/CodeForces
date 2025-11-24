// Problem: CF 1965 E - Connected Cubes
// https://codeforces.com/contest/1965/problem/E

/*
 * Problem: Connected Cubes
 * Algorithm: Greedy approach with careful construction of additional cubes to ensure connectivity for each color.
 * 
 * Approach:
 * 1. Read input cubes and count occurrences of each color.
 * 2. Sort colors by frequency (descending), so we handle the most frequent color first.
 * 3. For each color group, we place additional cubes in a way that ensures that all cubes of that color 
 *    are connected through face-sharing.
 * 4. We build layers in 3D space where we add cubes to bridge disconnected components.
 * 
 * Time Complexity: O(n * m * k) due to processing each cube and layer
 * Space Complexity: O(n * m + k) for storing cube data and auxiliary arrays
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
const int N = 4e5 + 5;
int n, m, k, mm, a[99][99], c[55], p[55], t[55], tot, x[N], y[N], z[N], w[N];
#define add(X, Y, Z, W) x[++tot] = X, y[tot] = Y, z[tot] = Z, w[tot] = W;
int main() {
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      scanf("%d", &a[i][j]), c[a[i][j]]++; // Read input and count color frequencies
  for (int i = 1; i <= k; i++)
    p[i] = i; // Initialize color list
  sort(p + 1, p + k + 1,
       [](const int &i, const int &j) { return c[i] > c[j]; }); // Sort colors by frequency (descending)
  for (int i = 1; i <= m; i++)
    t[i] = i * 3 >> 1; // Precompute some index transformation values for layer planning
  mm = t[m] + (m & 1); // Determine maximum index for y-coordinate
  for (int l = 1; l < m; l++) {
    if (l > 1)
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= mm; j++)
          if (a[i][j])
            add(i, j, l, a[i][j]); // Add existing cubes to new layer if exists
    for (int i = 1; i <= n; i++) {
      for (int j = m - l + 2; j <= t[m - l + 1]; j++)
        add(i, j, l, a[i][m - l + 1]); // Fill in missing spots with cubes from the current color
      swap(a[i][m - l + 1], a[i][t[m - l + 1]]); // Swap positions to avoid overlap
    }
  }
  for (int l = m; l < m + k; l++)
    for (int i = 1; i <= n + 1; i++)
      for (int j = 1; j <= mm; j++) {
        if (a[i][j] && l > 1)
          add(i, j, l, a[i][j]); // Add a cube from current color if exists and layer is not 1
        if (j % 3 == 2 || i > n)
          add(i, j, l, p[l - m + 1]); // Add cube of target color to fill in 3D space
        if (a[i][j] == p[l - m + 1])
          a[i][j] = 0; // Mark that this color cube has been handled
      }
  cout << tot << endl; // Output total added cubes
  for (int i = 1; i <= tot; i++)
    printf("%d %d %d %d\n", x[i], y[i], z[i], w[i]); // Print all added cube positions and colors
}


// https://github.com/VaHiX/CodeForces/