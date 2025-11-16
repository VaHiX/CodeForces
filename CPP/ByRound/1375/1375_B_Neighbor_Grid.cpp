// Problem: CF 1375 B - Neighbor Grid
// https://codeforces.com/contest/1375/problem/B

/*
Purpose: This code solves the "Neighbor Grid" problem where we need to make a grid good by increasing values in cells. 
         A grid is good if each cell with value k > 0 has exactly k neighboring cells with value > 0.
         The algorithm attempts to assign each cell a value such that the condition holds.
         If impossible, it outputs "NO". Otherwise, it prints a valid configuration.

Algorithms/Techniques:
- Greedy approach with preprocessing:
  1. For each cell, determine how many neighbors it has (at most 4).
  2. If the cell's value is greater than the number of neighbors, it's impossible.
  3. Otherwise, greedily assign the number of neighbors to each cell as a valid solution.

Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for storing the grid

*/
#include <iostream>
#include <vector>
int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<long>> a(n, std::vector<long>(m, 0));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        std::cin >> a[row][col];
      }
    }
    bool possible(true);
    for (long row = 0; row < n; row++) {
      if (!possible) {
        break;
      }
      for (long col = 0; col < m; col++) {
        // Calculate number of neighbors for current cell
        long d = (row > 0) + (col > 0) + (row + 1 < n) + (col + 1 < m);
        // If current value exceeds number of neighbors, it's impossible to satisfy condition
        if (a[row][col] > d) {
          possible = false;
          break;
        } else {
          // Assign number of neighbors as value for the cell
          a[row][col] = d;
        }
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
    if (possible) {
      for (long row = 0; row < n; row++) {
        for (long col = 0; col < m; col++) {
          std::cout << a[row][col] << " ";
        };
        std::cout << std::endl;
      };
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/