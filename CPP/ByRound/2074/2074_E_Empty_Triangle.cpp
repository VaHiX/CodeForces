// Problem: CF 2074 E - Empty Triangle
// https://codeforces.com/contest/2074/problem/E

/*
 * Problem: E. Empty Triangle
 * Purpose: Find a triangle formed by three given points such that no other point lies inside it.
 * Algorithm: Iteratively query triangles using a sliding window approach to eliminate points inside triangles.
 *            The process starts with three initial points and keeps updating the triangle until a valid empty one is found.
 * Time Complexity: O(n) per test case in average scenario, since we traverse points linearly to find an empty triangle.
 * Space Complexity: O(1), only using a few variables for tracking indices and query results.
 */
#include <stdio.h>
#include <iostream>

using namespace std;

void solve() {
  int n, q;
  cin >> n;
  // Initialize three points for the first query
  int x = 1, y = n / 2 + 1, z = n;
  printf("? %d %d %d\n", x, y, z);
  cin >> q;
  // Keep querying while the result is not zero (i.e., a point is inside the triangle)
  while (q != 0) {
    // Slide the window
    x = y;
    y = z;
    z = q;
    printf("? %d %d %d\n", x, y, z);
    cin >> q;
  }
  // Output the final valid triangle (no point inside)
  printf("! %d %d %d\n", x, y, z);
  return;
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/