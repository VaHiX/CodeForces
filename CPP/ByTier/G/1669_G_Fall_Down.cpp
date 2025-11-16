// Problem: CF 1669 G - Fall Down
// https://codeforces.com/contest/1669/problem/G

/*
Algorithm/Techniques: Simulation, Greedy Approach
Time Complexity: O(n * m) where n is the number of rows and m is the number of columns.
Space Complexity: O(n * m) for storing the grid.

This code simulates the process of stones falling down in a grid until they hit the bottom,
an obstacle, or another stone. It processes each column from bottom to top, moving stones
downwards as much as possible, stopping only when they meet an obstacle or another stone.

The algorithm works by:
- For each column, we track the lowest available position (b) where a stone can fall.
- Traverse from bottom to top of the column.
- When we encounter a stone (*), we move it to the current lowest available position and update that position.
- When we encounter an obstacle (o), we set the next available position to be just above it.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long nr, nc;
    std::cin >> nr >> nc;
    std::vector<std::string> v(nr);
    for (long row = 0; row < nr; row++) {
      std::cin >> v[row];
    }
    for (long col = 0; col < nc; col++) {
      long b(nr - 1);  // b tracks the lowest available position in the column
      for (long row = nr - 1; row >= 0; row--) {
        if (v[row][col] == '*') {
          v[row][col] = '.';     // Remove the stone from current position
          v[b][col] = '*';       // Place the stone at the lowest available position
          --b;                   // Move the available position up
        } else if (v[row][col] == 'o') {
          b = row - 1;           // Obstacle stops further movement; set next available position above it
        }
      }
    }
    for (long row = 0; row < nr; row++) {
      std::cout << v[row] << std::endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/