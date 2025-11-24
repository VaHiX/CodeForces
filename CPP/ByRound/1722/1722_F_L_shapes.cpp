// Problem: CF 1722 F - L-shapes
// https://codeforces.com/contest/1722/problem/F

/*
Algorithm/Techniques: Brute Force with Bit Manipulation
Time Complexity: O(n^2 * m^2) per test case, where n and m are grid dimensions.
Space Complexity: O(n * m) for storing the grid.

This code checks whether a given grid can be decomposed entirely into valid
L-shapes, where each L-shape consists of exactly 3 shaded cells forming an
L-shape and no two L-shapes can touch by edge or corner. The approach uses
brute-force to verify each shaded cell belongs to a valid L-shape and that
L-shapes do not overlap or touch.

The expression (abs(i - k) | abs(j - l)) + g[k][l] == 43 is used to detect if a
cell is part of an L-shape. It checks for combinations that form valid L-shape
patterns.

*/
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;
#define F(i, r) for (int i = 0; i < r; ++i)
string g[50], s;
int t, n, m, p, q, c;
int main() {
  cin >> t;
  F(u, t) {
    cin >> n >> m;
    F(i, n) cin >> g[i];
    s = "YES ";
    F(i, n)
    F(j, m) if (g[i][j] - 46) { // Check if current cell is a shaded cell (*)
      p = q = c = 1;
      F(k, n)
      F(l, m)
      if ((abs(i - k) | abs(j - l)) + g[k][l] == 43) p *=
          k - i,           // Compute product of coordinate differences
          q *= l - j, c++; // Count matching cells and update products
      if (c - 3 | (p | q) * (p + q - 1)) // Check if 3 cells form an L-shape and
                                         // satisfy the constraints
        s = "NO ";
    }
    cout << s << endl;
  }
}

// https://github.com/VaHiX/CodeForces/