// Problem: CF 1426 B - Symmetric Matrix
// https://codeforces.com/contest/1426/problem/B

/*
B. Symmetric Matrix
Algorithm: Check if we can construct an m x m symmetric matrix using given 2x2 tiles.
Time Complexity: O(n * m^2) - For each test case, we iterate through all n tile types for each cell in the matrix (but only check necessary conditions).
Space Complexity: O(1) - Only fixed-size variables are used.

The approach is based on symmetry properties:
- For a symmetric matrix, elements at positions (i,j) and (j,i) must be equal.
- Each tile is 2x2, so we need to place them carefully to ensure symmetry.
- If m is odd, it's impossible to create a valid symmetric matrix since there will be a middle cell that doesn't have a pair.
- For each tile type, if x == y (middle elements of the tile), then it's valid for center symmetry.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    bool possible(false); // Flag to track if solution is possible
    for (long p = 0; p < n; p++) {
      long w, x, y, z;
      scanf("%ld%ld%ld%ld", &w, &x, &y, &z); // Read tile: top-left, top-right, bottom-left, bottom-right
      if (x == y) { // If middle elements of tile are equal, it can be placed symmetrically
        possible = true;
      }
    }
    if (m % 2) { // If m is odd, center cell exists and requires specific arrangement
      possible = false;
    }
    puts(possible ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/