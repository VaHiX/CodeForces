// Problem: CF 1772 B - Matrix Rotation
// https://codeforces.com/contest/1772/problem/B

/*
B. Matrix Rotation
time limit per test2 seconds
memory limit per test512 megabytes

Problem Description:
You have a 2x2 matrix filled with distinct integers. You want to make the matrix "beautiful" by ensuring:
1. In each row, the first element is smaller than the second element.
2. In each column, the first element is smaller than the second element.

You can rotate the matrix 90 degrees clockwise any number of times. Determine if it's possible to make the matrix beautiful after zero or more rotations.

Algorithm:
The key insight is that there are only four possible orientations of a 2x2 matrix after rotation (including original). We check all four rotations to see if any of them satisfies the beautiful condition.

Time Complexity: O(1) - Since we always process a fixed-size 2x2 matrix and check a constant number of cases.
Space Complexity: O(1) - Only using a constant amount of extra space.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, z, w;
    scanf("%ld %ld %ld %ld", &x, &y, &z, &w);
    // Check all possible rotations for the beautiful condition
    bool ans = (x < y && x < z && y < w && z < w) ||        // Original orientation
               (z < x && z < w && x < y && w < y) ||        // 90° clockwise
               (w < z && w < y && z < x && y < x) ||        // 180° clockwise
               (y < w && y < x && w < z && x < z);          // 270° clockwise
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/