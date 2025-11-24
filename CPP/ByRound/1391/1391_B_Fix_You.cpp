// Problem: CF 1391 B - Fix You
// https://codeforces.com/contest/1391/problem/B

/*
B. Fix You
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Problem Description:
We are given a grid of n rows and m columns representing a conveyor belt. Each cell (except the bottom-right corner) has a direction: 'R' (right) or 'D' (down). Luggage placed at any cell follows the directions until it exits the grid or reaches the counter at (n, m). The goal is to find the minimum number of cells to change so that all paths lead to the counter.

Algorithm:
- The key insight is that if we can reach the bottom-right corner without needing to change anything, nothing needs to be changed. 
- But if a path leads away from the destination or fails to get there, we need to fix it.
- For each cell on the last column (from top to bottom), check if its direction is 'R'. If so, then luggage would exit right and never reach (n,m); hence it must be changed to 'D'.
- Similarly, for each cell on the last row (left to right), check if its direction is 'D'. If so, luggage would move down and exit grid; it must be changed to 'R'.

Time Complexity: O(n * m) - We scan the grid twice.
Space Complexity: O(n * m) - For storing the grid.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> a(n);
    for (long p = 0; p < n; p++) {
      std::cin >> a[p]; // Read the grid row by row
    }
    long cnt(0);
    // Count how many cells in the last column need to be changed to 'D'
    for (long p = 0; p < n; p++) {
      cnt += (a[p][m - 1] == 'R'); // If direction is 'R', must change it
    }
    // Count how many cells in the last row need to be changed to 'R'
    for (long p = 0; p < m; p++) {
      cnt += (a[n - 1][p] == 'D'); // If direction is 'D', must change it
    }
    std::cout << cnt << std::endl; // Output minimal changes needed
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/