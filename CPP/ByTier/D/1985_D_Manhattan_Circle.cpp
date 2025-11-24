// Problem: CF 1985 D - Manhattan Circle
// https://codeforces.com/contest/1985/problem/D

/*
 * Problem: D. Manhattan Circle
 *
 * Purpose: Given an n x m grid where '#' represents points inside a Manhattan circle,
 *          find the center of that circle. A Manhattan circle centered at (h, k) with
 *          radius r includes all points (a, b) such that |h - a| + |k - b| < r.
 *
 * Algorithm:
 *   - For each '#' in the grid, accumulate the row and column indices.
 *   - Compute the average of these coordinates to estimate the center of mass.
 *   - The average gives the approximate center of the Manhattan circle.
 *
 * Time Complexity: O(n * m) per test case, since we visit each cell once.
 * Space Complexity: O(1), not counting input storage.
 */

#include <iostream>
#include <string>

typedef long long ll;

int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  std::cin >> t;
  while (t--) {
    ll n, m;
    std::cin >> n >> m;
    ll sr(0), sc(0), cnt(0); // sr: sum of row indices, sc: sum of column indices, cnt: number of '#' cells
    for (ll row = 0; row < n; row++) {
      std::string s;
      std::cin >> s;
      for (long col = 0; col < s.size(); col++) {
        if (s[col] == '.') {
          continue; // Skip empty cells
        }
        sr += 1 + row;  // Add 1 to convert from 0-based to 1-based coordinates
        sc += 1 + col;
        ++cnt;
      }
    }
    std::cout << (sr / cnt) << " " << (sc / cnt) << std::endl; // Output the average coordinate (center)
  }
}


// https://github.com/VaHiX/codeForces/