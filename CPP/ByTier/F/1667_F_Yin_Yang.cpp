// Problem: CF 1667 F - Yin Yang
// https://codeforces.com/contest/1667/problem/F

/*
Algorithm: Yin Yang Grid Coloring
This code solves the problem of coloring a grid such that both black and white
components form orthogonally connected regions. The approach uses a combination
of boundary filling, rotation optimization, stripe coloring, and connection
repair techniques.

Time Complexity: O(n*m) per test case, where n and m are grid dimensions
Space Complexity: O(n*m) for storing the grid and auxiliary arrays

Techniques used:
1. Boundary filling with alternating colors
2. Rotation optimization to find good orientation
3. Stripe-based coloring with 4-row pattern
4. Connection repair for isolated components
5. Bridging through stripes for connectivity

The algorithm first handles fixed cells, then applies a series of operations
to ensure both black and white components form connected regions.
*/
#include <bits/stdc++.h>
using namespace std;

const int c = 505;
int t, n, m, fix[c][c], ans[c][c], rotcnt, change, old_cl, new_cl;
int fix2[c][c], ans2[c][c];
void color_boundary() {
  // Fill the grid boundary (top row, right column, bottom row, left column)
  // with colors propagated from fixed cells. The loop runs twice: the first
  // pass establishes values and the second counts transitions (change). The
  // `change` counter tracks the number of color transitions along the
  // boundary which is used to quickly reject impossible configurations.
  for (int cnt = 1; cnt <= 2; cnt++) {
    for (int j = 2; j <= m; j++) {
      if (!ans[1][j])
        ans[1][j] = ans[1][j - 1];
      if (ans[1][j] != ans[1][j - 1])
        change++;
    }
    for (int i = 2; i <= n; i++) {
      if (!ans[i][m])
        ans[i][m] = ans[i - 1][m];
      if (ans[i][m] != ans[i - 1][m])
        change++;
    }
    for (int j = m - 1; j >= 1; j--) {
      if (!ans[n][j])
        ans[n][j] = ans[n][j + 1];
      if (ans[n][j] != ans[n][j + 1])
        change++;
    }
    for (int i = n - 1; i >= 1; i--) {
      if (!ans[i][1])
        ans[i][1] = ans[i + 1][1];
      if (ans[i][1] != ans[i + 1][1])
        change++;
    }
    if (!ans[1][1])
      ans[1][1] = 1;
    if (cnt == 1)
      change = 0;
  }
}
void rotate_90() {
  // Rotate the grid 90 degrees clockwise. This updates both `ans` and
  // `fix` arrays and swaps `n` and `m`. `rotcnt` counts performed rotations
  // so we can restore orientation at the end.
  rotcnt++;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans2[i][j] = ans[i][j], fix2[i][j] = fix[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans[j][n + 1 - i] = ans2[i][j];
      fix[j][n + 1 - i] = fix2[i][j];
    }
  }
  swap(n, m);
}
void good_rotation() {
  // Try up to 4 rotations to find an orientation where the boundary colors
  // adhere to a desired pattern: most cells on the first column equal to
  // ans[1][1] and at least one opposing color visible near the top-right
  // corner. If current orientation is not satisfactory we rotate.
  for (int cnt = 1; cnt <= 4; cnt++) {
    bool same = 1, opposite = 0;
    for (int i = 1; i <= n; i++) {
      if (ans[i][1] != ans[1][1])
        same = 0;
      if (1 < i && i < n && ans[1][1] != ans[i][m])
        opposite = 1;
    }
    if (!same || !opposite)
      rotate_90();
  }
}
void color_the_stripes() {
  // Paint internal cells in 4-row repeating stripes: rows with indices
  // congruent to 2 or 3 (mod 4) receive `old_cl`, the others receive
  // `new_cl`. Fixed cells (`fix[i][j] != 0`) are left untouched.
  for (int i = 2; i < n; i++) {
    for (int j = 2; j < m; j++) {
      if (!fix[i][j]) {
        if (i % 4 == 2 || i % 4 == 3)
          ans[i][j] = old_cl;
        else
          ans[i][j] = new_cl;
      }
    }
  }
}
void avoid_touching() {
  // Small local repair: detect and fix 2x2 configurations where diagonal
  // equality would force two same-colored regions to touch incorrectly.
  // We flip the non-fixed cell among the offending pair to avoid touching.
  for (int i = 1; i < n; i++) {
    if (ans[i][m - 1] == ans[i + 1][m] && ans[i + 1][m - 1] == ans[i][m] &&
        ans[i][m] != ans[i + 1][m]) {
      if (!fix[i][m])
        ans[i][m] = 3 - ans[i][m];
      else
        ans[i + 1][m] = 3 - ans[i + 1][m];
    }
  }
}
void boundary_stripe_connection() {
  // Ensure the boundary stripe (rightmost column) of `new_cl` is connected
  // to the interior stripes when its occurrences are concentrated near an
  // edge. We check simple patterns and carve a small corridor if needed to
  // connect the boundary stripe into the main `new_cl` region.
  int first = 0, last = 0;
  for (int i = 1; i <= n; i++) {
    if (ans[i][m] == new_cl) {
      if (!first)
        first = i;
      last = i;
    }
  }
  if (first == 0 || (last > 3 && first < n - 2))
    return;
  if (last <= 3 && fix[4][m - 1] == old_cl) {
    for (int i = 3; i <= 5; i++) {
      ans[i][m] = new_cl;
    }
    return;
  }
  if (first >= n - 2 && fix[n - 3][m - 1] == old_cl) {
    for (int i = n - 4; i <= n - 2; i++) {
      ans[i][m] = new_cl;
    }
    return;
  }
  int x = (last <= 3 ? 2 : n - 2);
  for (int i = x; i <= x + 1; i++) {
    for (int j = m - 1; j <= m; j++) {
      if (!fix[i][j])
        ans[i][j] = new_cl;
    }
  }
}
void connect_isolated_point(int x, int y) {
  // Connect a potentially isolated `new_cl` cell at (x,y) to the nearest
  // `new_cl` region. The routine considers short paths and checks nearby
  // fixed cells to decide where to place bridging cells. This is a small
  // heuristic repair to guarantee connectivity for the `new_cl` color.
  if (ans[x - 1][y] == new_cl || ans[x + 1][y] == new_cl ||
      ans[x][y + 1] == new_cl)
    return;
  int x1 = (x == 2 ? 1 : n), x2 = (x == 2 ? 2 : n - 1),
      x3 = (x == 2 ? 3 : n - 2), x4 = (x == 2 ? 4 : n - 3);
  if (y <= m - 2 && ans[x1][y + 2] == new_cl) {
    ans[x1][y] = new_cl;
    ans[x1][y + 1] = new_cl;
    return;
  }
  if (y <= m - 2 && ans[x2][y + 2] == new_cl) {
    ans[x2][y + 1] = new_cl;
    return;
  }
  if (fix[x4][y] != old_cl) {
    ans[x3][y] = new_cl;
  } else {
    int y2 = (y + 1 < m ? y + 1 : y - 1);
    ans[x2][y2] = new_cl;
    ans[x3][y2] = new_cl;
  }
}
void bridge_through_the_stripe(int x) {
  // Attempt to build a vertical bridge across the stripe starting at row x
  // to connect the left boundary color to the rightmost stripe. The function
  // prefers free columns (2..4) and otherwise makes conservative local
  // adjustments ensuring no fixed cells are violated.
  for (int j = 2; j <= 4; j++) {
    bool good = 1;
    for (int i = x - 1; i <= x + 2; i++) {
      if (fix[i][j] == old_cl)
        good = 0;
    }
    if (good) {
      ans[x][j] = new_cl;
      ans[x + 1][j] = new_cl;
      return;
    }
  }
  for (int i = x - 1; i <= x + 2; i++) {
    if (!fix[i][3])
      ans[i][3] = new_cl;
  }
  if (fix[x - 1][3]) {
    ans[x - 1][2] = old_cl;
    ans[x][4] = new_cl;
  }
  if (fix[x + 2][3]) {
    ans[x + 2][2] = old_cl;
    ans[x + 1][4] = new_cl;
  }
  if (fix[x][3] || fix[x + 1][3]) {
    ans[x][2] = new_cl;
    ans[x + 1][2] = new_cl;
  }
}
main(void) {
  // Main driver: read test cases, parse the grid, apply the constructive
  // procedure, and either print "NO" when impossible or output a valid
  // coloring with both colors connected.
  cin >> t;
  for (int tc = 1; tc <= t; tc++) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        char c;
        cin >> c;
        fix[i][j] = (c == 'B' ? 1 : c == 'W' ? 2 : 0);
        ans[i][j] = fix[i][j];
      }
    }
    // Step 1: propagate colors around the boundary and count transitions
    color_boundary();
    // A large number of boundary transitions implies impossible layout
    if (change >= 4) {
      cout << "NO\n";
    } else {
      // Try to orient the grid to a favorable rotation
      good_rotation();
      // old_cl is the dominant color at top-left; new_cl is the other
      old_cl = ans[1][1], new_cl = 3 - ans[1][1];
      // Paint interior stripes and perform a series of local repairs
      color_the_stripes();
      avoid_touching();
      boundary_stripe_connection();
      // Connect isolated new_cl points near the top and bottom stripes
      for (int j = 2; j < m; j++) {
        if (fix[2][j] == new_cl)
          connect_isolated_point(2, j);
        if (fix[n - 1][j] == new_cl)
          connect_isolated_point(n - 1, j);
      }
      // Try to bridge the left boundary through interior stripes every 4 rows
      for (int i = 6; i <= n - 6; i += 4) {
        if (ans[1][1] == ans[i][m] || ans[1][1] == ans[i + 1][m])
          bridge_through_the_stripe(i);
      }
      // Restore original orientation and print the result
      while (rotcnt < 4)
        rotate_90();
      cout << "YES\n";
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          cout << (ans[i][j] == 1 ? "B" : "W");
        }
        cout << "\n";
      }
    }
    rotcnt = 0, change = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        fix[i][j] = 0, ans[i][j] = 0;
        fix[j][i] = 0, ans[j][i] = 0;
      }
    }
  }
}

// https://github.com/VaHiX/CodeForces/