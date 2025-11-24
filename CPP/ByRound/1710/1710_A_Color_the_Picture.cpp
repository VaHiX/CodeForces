// Problem: CF 1710 A - Color the Picture
// https://codeforces.com/contest/1710/problem/A

/*
 * Problem: A. Color the Picture
 * 
 * Purpose: Determine if it's possible to color an n×m grid using k pigments such that
 *          each cell has at least 3 toroidal neighbors of the same color.
 * 
 * Algorithm:
 * - For a valid coloring, each cell must have at least 3 neighbors with the same color.
 * - The key insight is that cells are arranged in a toroidal grid (wrap around edges),
 *   and each cell has exactly 4 neighbors.
 * - A beautiful picture can be constructed if we can assign colors such that
 *   the constraints on neighbor counts are satisfied.
 * 
 * Approach:
 * - We check both dimensions (n, m) and (m, n) to account for rotation possibilities.
 * - The function `Solve(n, m)` counts how many full sets of 3 cells we can form from each pigment,
 *   and ensures there's at least one pigment providing ≥ 3/2 sets (i.e., at least one set with 3 cells).
 * - This is based on the fact that if we group cells (i.e., for a valid coloring),
 *   we need at least 3 neighbors of same color — meaning we can use each pigment
 *   to cover parts of a larger structure.
 * 
 * Time Complexity: O(k) per test case due to single pass through array 'a'.
 * Space Complexity: O(k) for storing array 'a'.
 */
#include <stdio.h>

const int K = 1e5 + 3;
int n, m, k, a[K];

// Check if we can form a beautiful grid with given n and m dimensions
bool Solve(int n, int m) {
  bool fl = 0;              // flag to track if any pigment allows >= 3 cells per group
  long long mx = 0;         // total number of full 2-cell groups possible from pigments
  for (int i = 1; i <= k; i++)
    if (a[i] / m >= 2)      // check if we can form at least 2 groups with each pigment
      mx += a[i] / m,       // add number of groups formed
      fl |= a[i] / m >= 3;  // set flag if some pigment supports ≥ 3 groups
  return (~n & 1 || fl) && mx >= n;  // combine conditions about parity and group count
}

int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
      scanf("%d", a + i);   // read pigment limits
    puts(Solve(n, m) || Solve(m, n) ? "Yes" : "No"); // try both orientations
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/