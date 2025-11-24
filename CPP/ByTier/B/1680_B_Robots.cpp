// Problem: CF 1680 B - Robots
// https://codeforces.com/contest/1680/problem/B

/*
B. Robots
Purpose: Determine whether it's possible to move at least one robot to the top-left corner (0,0) without any robot exploding by moving outside the grid.
Algorithms/Techniques: 
  - Greedy approach with simulation of robot movement
  - Find the lowest-rightmost 'R' robot and ensure that all robots to its left and above it can reach (0,0) by moving in valid directions.

Time Complexity: O(n * m) per test case, where n and m are the number of rows and columns.
Space Complexity: O(n * m) for storing the grid.

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> f(n);
    for (long row = 0; row < n; row++) {
      std::cin >> f[row];
    }
    // Find the bottom-rightmost 'R' robot
    long br(-1), bc(-1);
    for (long row = 0; br < 0 && row < n; row++) {
      for (long col = 0; bc < 0 && col < m; col++) {
        if (f[row][col] == 'R') {
          br = row;
          bc = col;
          break;
        }
      }
    }
    bool possible(true);
    // Check if any robot exists in the area that would block path to (0,0)
    for (long row = br + 1; possible && row < n; row++) {
      for (long col = 0; possible && col < bc; col++) {
        if (f[row][col] == 'R') {
          possible = false;
          break;
        }
      }
    }
    std::cout << (possible ? "YES" : "NO") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/