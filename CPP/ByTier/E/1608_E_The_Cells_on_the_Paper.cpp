// Problem: CF 1608 E - The Cells on the Paper
// https://codeforces.com/contest/1608/problem/E

/*
Algorithm: Binary search on the answer with brute-force permutation check for valid rectangle placement.
Time Complexity: O(n^2 * log(n)) where n is the number of cells per color.
Space Complexity: O(n) for storing and sorting cell coordinates.

The problem asks to find the maximum number k such that we can select k/3 cells of each color,
and place them into three non-overlapping rectangles.

Key insights:
1. For each color, we try all possible ways to place the cells in a rectangle.
2. A cell (x, y) can be part of a rectangle defined by (x1, y1) to (x2, y2) where x1 <= x <= x2 and y1 <= y <= y2.
3. To avoid overlap of rectangles: we can place rectangles in different octants or configurations.
4. For each octant configuration and color permutation, we validate if three rectangles can be formed.
5. Binary search is used over the possible k value to maximize it.
*/

#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

#define pii pair<int, int>
#define fr first
#define sc second
#define inf ((int)1e9 + 1)
#define N 100005
using namespace std;
int n;
vector<pii> B[3], A[8][3];
inline bool chk(int x) {
  int p[3] = {0, 1, 2}; // Permutation array for color ordering
  do {
    for (int o = 0; o < 4; o++) { // 4 octant configurations
      int u = A[o << 1][p[0]][x - 1].fr + 1; // x-coordinate of 1st color's rectangle
      int y = x, v = inf; // Initialize search
      for (auto [i, j] : A[o << 1][p[1]]) // Iterate through second color's cells
        if (i >= u && !--y) { // Found a valid boundary
          v = i + 1;
          break;
        }
      y = x;
      for (auto [i, j] : A[o << 1][p[2]]) // Check third color for compatibility
        if (i >= v && !--y) // Check if valid
          return 1;
      y = x, v = inf;
      for (auto [i, j] : A[o << 1 | 1][p[1]]) // Next octant
        if (i >= u && !--y) {
          v = j + 1;
          break;
        }
      y = x;
      for (auto [i, j] : A[o << 1 | 1][p[2]]) // Third color in new octant
        if (i >= u && j >= v && !--y) // Validate rectangle placement
          return 1;
    }
  } while (next_permutation(p, p + 3)); // Try all permutations of color order
  return 0; // No valid configuration found
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    B[c - 1].emplace_back(x, y); // Store cells grouped by color, 0-based indexing
  }
  for (int oo = 0; oo < 2; oo++) { // Flip x sign for two orientations
    for (int o = 0; o < 2; o++) {
      for (int i = 0; i < 3; i++) {
        A[(oo << 2) | (o << 1)][i] = B[i]; // Copy to orientation-based array
        sort(A[(oo << 2) | (o << 1)][i].begin(), // Sort x,y
             A[(oo << 2) | (o << 1)][i].end());
        A[(oo << 2) | (o << 1) | 1][i] = B[i]; // Next orientation
        sort(A[(oo << 2) | (o << 1) | 1][i].begin(), // Sort by y then x
             A[(oo << 2) | (o << 1) | 1][i].end(),
             [](const pii &u, const pii &v) {
               return u.sc == v.sc ? u.fr < v.fr : u.sc < v.sc;
             });
      }
      for (int i = 0; i < 3; i++) // Flip x coordinate in each group
        for (int j = 0; j < n / 3; j++)
          B[i][j].fr *= -1;
    }
    for (int i = 0; i < 3; i++) // Transpose coordinates
      for (int j = 0; j < n / 3; j++)
        swap(B[i][j].fr, B[i][j].sc);
  }
  int L = 1, R = n / 3, res = L; // Binary search bounds
  while (L <= R) {
    int mid = (L + R) >> 1; // Mid-point for binary search
    if (chk(mid)) // If valid configuration exists
      res = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  printf("%d\n", 3 * res); // Output final k value
}


// https://github.com/VaHiX/CodeForces/