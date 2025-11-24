// Problem: CF 462 A - Appleman and Easy Task
// https://codeforces.com/contest/462/problem/A

/*
 * Problem: Appleman and Easy Task
 * 
 * Description:
 * Given an n x n checkerboard filled with 'x' and 'o', determine if every cell has an even number 
 * of adjacent 'o' cells. Adjacent means sharing a side (up, down, left, right).
 * 
 * Algorithm:
 * - For each cell in the grid, count the number of adjacent 'o' cells.
 * - If any cell has an odd number of adjacent 'o's, output "NO", otherwise "YES".
 * 
 * Time Complexity: O(n^2) - We process each cell once and check at most 4 neighbors.
 * Space Complexity: O(n^2) - To store the n x n grid.
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
int main() {
  int n;
  scanf("%d\n", &n);
  std::vector<std::string> checkboard(n);
  for (int p = 0; p < n; p++) {
    getline(std::cin, checkboard[p]);
  }
  bool allEven(1); // Assume all cells satisfy the condition
  for (int row = 0; row < n; row++) {
    if (!allEven) {
      break; // Early exit if condition fails
    }
    for (int col = 0; col < n; col++) {
      int adjacent = 0;
      // Check all four adjacent cells (up, down, left, right)
      if (row > 0 && checkboard[row - 1][col] == 'o') {
        ++adjacent;
      }
      if (row < n - 1 && checkboard[row + 1][col] == 'o') {
        ++adjacent;
      }
      if (col > 0 && checkboard[row][col - 1] == 'o') {
        ++adjacent;
      }
      if (col < n - 1 && checkboard[row][col + 1] == 'o') {
        ++adjacent;
      }
      // If number of adjacent 'o's is odd, the condition is violated
      if (adjacent % 2 > 0) {
        allEven = false;
        break;
      }
    }
  }
  puts(allEven ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/