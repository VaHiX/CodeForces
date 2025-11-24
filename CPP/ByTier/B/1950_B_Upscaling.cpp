// Problem: CF 1950 B - Upscaling
// https://codeforces.com/contest/1950/problem/B

/*
B. Upscaling

Algorithm:
The program generates a 2n×2n checkerboard made of 2×2 squares.
Each 2×2 square alternates between '#' and '.' patterns.
The top-left cell is '#'.
The entire board is constructed by:
1. Creating two strings s and t which represent alternating rows.
   - s starts with "##" (row of '#') followed by ".."
   - t starts with ".." (row of '.') followed by "##"
2. For each row in the 2n×2n grid, select between s and t based on row index:
   - Rows with indices 0-1 use s
   - Rows with indices 2-3 use t
   - And so on, alternating every two rows

Time Complexity: O(n^2)
Space Complexity: O(n^2)

*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s, t;
    for (int p = 0; p < n; p++) {
      s += (p % 2 ? ".." : "##");  // Build s with alternating ".." and "##"
      t += (p % 2 ? "##" : "..");  // Build t with alternating "##" and ".."
    }
    for (int row = 0; row < 2 * n; row++) {
      std::cout << (row % 4 < 2 ? s : t) << std::endl;  // Alternate between s and t every 2 rows
    }
  }
}


// https://github.com/VaHiX/codeForces/