// Problem: CF 1952 F - Grid
// https://codeforces.com/contest/1952/problem/F

#include <iostream>
#include <vector>
#include <string>

/*
F. Grid
Input: 21x21 grid of '0' and '1' characters.
Task: Find the maximum sum of '1's in any 4x4 subgrid.
Algorithm: Brute-force sliding window approach.
Time Complexity: O(B^2) where B = 21, so effectively O(1).
Space Complexity: O(B^2) for storing the grid.

*/

int main() {
  const int B = 21; // Size of the grid
  const int b = 4;  // Size of the subgrid to check
  std::ios_base::sync_with_stdio(false); // Optimize I/O
  std::vector<std::string> v(B); // Store the input grid
  for (long row = 0; row < B; row++) {
    std::cin >> v[row]; // Read each row of the grid
  }
  long mxcnt(0); // Initialize maximum count of '1's found
  for (long row = 0; row + b <= B; row++) { // Slide the window row-wise
    for (long col = 0; col + b <= B; col++) { // Slide the window column-wise
      long tst(0); // Temporary count of '1's in current subgrid
      for (long sr = 0; sr < b; sr++) { // Iterate through rows of subgrid
        for (long sc = 0; sc < b; sc++) { // Iterate through columns of subgrid
          tst += (v[row + sr][col + sc] - '0'); // Add value (0 or 1) to count
        }
      }
      mxcnt = (mxcnt > tst ? mxcnt : tst); // Update maximum
    }
  }
  std::cout << mxcnt << std::endl; // Output the result
}

// https://github.com/VaHiX/codeForces/