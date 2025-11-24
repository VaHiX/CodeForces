// Problem: CF 1703 E - Mirror Grid
// https://codeforces.com/contest/1703/problem/E

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    long total(0);
    // Traverse only the top-left quarter of the grid to process symmetric groups
    for (long row = 0; row < n / 2; row++) {
      for (long col = row; col < n - 1 - row; col++) {
        // Get the four symmetric positions in the grid
        char a = v[row][col];                           // Top-left
        char b = v[col][n - 1 - row];                   // Top-right
        char c = v[n - 1 - row][n - 1 - col];           // Bottom-right
        char d = v[n - 1 - col][row];                   // Bottom-left
        
        // Count how many of the four positions have '1' and '0'
        int cntZ = (a == '1') + (b == '1') + (c == '1') + (d == '1');
        int cntA = (a == '0') + (b == '0') + (c == '0') + (d == '0');
        
        // Add the minimum flips needed to make all four equal
        total += (cntZ < cntA ? cntZ : cntA);
      }
    }
    std::cout << total << std::endl;
  }
}

/*
E. Mirror Grid

Purpose:
This code solves a problem where we are given a square grid of 0s and 1s, and need to find the minimum number of operations 
to make the grid look identical under rotations of 0°, 90°, 180°, and 270°. This requires symmetry across all four rotations.

Approach:
- For each group of four symmetric positions in the grid (forming a 2x2 block of symmetry), 
  we calculate how many 1s and 0s exist among them.
- The minimal flips to make all four equal is the minimum of these two counts.
- We only iterate through one quarter of the grid to avoid double counting.

Time Complexity: O(n^2) - We visit each cell once in a symmetric manner.
Space Complexity: O(n^2) - Store the grid.
*/

// https://github.com/VaHiX/codeForces/