// Problem: CF 2044 H - Hard Demon Problem
// https://codeforces.com/contest/2044/problem/H

/*
Algorithm/Techniques: 2D Binary Indexed Tree (Fenwick Tree) with prefix sums and coordinate compression.
Time Complexity: O(n^2 + q) per test case, where n is the size of the matrix and q is the number of queries.
Space Complexity: O(n^2) for storing prefix sums and the matrix.

This code uses 2D prefix sums to quickly calculate submatrix sums and weighted sums.
It pre-processes the matrix to support fast queries by building prefix sums for:
- The original matrix values
- Weighted sums with respect to x-coordinates
- Weighted sums with respect to y-coordinates

Each query computes the required sum using inclusion-exclusion principle on these precomputed prefix sums.
*/

#include <iostream>

using namespace std;
long long origin[2001][2001] = {0}; // Prefix sum of matrix values
long long xsum[2001][2001] = {0}, ysum[2001][2001] = {0}; // Prefix sums of weighted values
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int temp;
        cin >> temp;
        // Build 2D prefix sum for original matrix
        origin[i][j] =
            origin[i - 1][j] + origin[i][j - 1] - origin[i - 1][j - 1] + temp;
        // Build 2D prefix sum for x-weighted values
        xsum[i][j] =
            xsum[i - 1][j] + xsum[i][j - 1] - xsum[i - 1][j - 1] + i * temp;
        // Build 2D prefix sum for y-weighted values
        ysum[i][j] =
            ysum[i - 1][j] + ysum[i][j - 1] - ysum[i - 1][j - 1] + j * temp;
      }
    }
    while (q--) {
      int x1, x2, y1, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      long long count = 0;
      // Get sum of submatrix values using prefix sum
      long long sumxy = origin[x2][y2] - origin[x1 - 1][y2] -
                        origin[x2][y1 - 1] + origin[x1 - 1][y1 - 1];
      count += sumxy;
      // Adjust for y-coordinate weighted sum
      count += ysum[x2][y2] - ysum[x1 - 1][y2] - ysum[x2][y1 - 1] +
               ysum[x1 - 1][y1 - 1] - sumxy * y1;
      // Adjust for x-coordinate weighted sum
      count +=
          (y2 - y1 + 1) * (xsum[x2][y2] - xsum[x1 - 1][y2] - xsum[x2][y1 - 1] +
                           xsum[x1 - 1][y1 - 1] - sumxy * x1);
      cout << count << ' ';
    }
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/