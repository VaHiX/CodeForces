// Problem: CF 1106 A - Lunar New Year and Cross Counting
// https://codeforces.com/contest/1106/problem/A

/*
 * Problem: Lunar New Year and Cross Counting
 *
 * Purpose:
 *   This program counts the number of "crosses" in an n×n matrix composed of 'X' and '.' characters.
 *   A cross is defined as a center character 'X' positioned at (i, j) such that the four diagonal
 *   neighbors are also 'X': (i-1, j-1), (i-1, j+1), (i+1, j-1), and (i+1, j+1).
 *
 * Algorithms/Techniques:
 *   - Brute Force Grid Traversal: The algorithm checks every possible center position (row, col)
 *     within the bounds where a cross can exist, i.e., 1 < row < n-1 and 1 < col < n-1.
 *   - Pattern Matching: For each candidate center, it verifies if all required diagonal positions
 *     have the value 'X'.
 *
 * Time Complexity:
 *   O(n^2) - We iterate through each cell in the grid once to check for potential crosses.
 *
 * Space Complexity:
 *   O(n^2) - Storage for the matrix of size n×n.
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n;
  std::cin >> n;
  std::vector<std::string> a(n); // Store the matrix
  for (long p = 0; p < n; p++) {
    std::cin >> a[p]; // Read each row of the matrix
  }
  long cnt(0); // Counter for number of crosses found
  for (long row = 1; row < n - 1; row++) { // Iterate over possible cross centers (excluding borders)
    for (long col = 1; col < n - 1; col++) {
      if (a[row][col] == 'X' && a[row - 1][col - 1] == 'X' && // Check center and all diagonal neighbors
          a[row + 1][col + 1] == 'X' && a[row - 1][col + 1] == 'X' &&
          a[row + 1][col - 1] == 'X') {
        ++cnt; // Increment counter if all conditions are met
      }
    }
  }
  printf("%ld\n", cnt); // Output total count of crosses
  return 0;
}


// https://github.com/VaHiX/codeForces/