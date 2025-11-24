// Problem: CF 1607 E - Robot on the Board 1
// https://codeforces.com/contest/1607/problem/E

/*
E. Robot on the Board 1
Time Complexity: O(|s|) for each test case, where |s| is the length of the command string.
Space Complexity: O(1), as we only use a constant amount of extra space.

Algorithm:
- Simulate robot movements to find how far it can go in each direction (minx, maxx, miny, maxy).
- The starting point should be chosen such that all commands are executed without going out of bounds.
- Compute the optimal starting row and column based on movement boundaries.
- The final coordinates are translated from 0-based to 1-based indexing.

Techniques:
- Prefix sum simulation for movement in 2D grid
- Coordinate transformation to find best start position
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    long x(0), y(0), minx(0), maxx(0), miny(0), maxy(0);
    for (char c : s) {
      if (c == 'L') {
        --y; // Move left decreases column index
        miny = (miny < y ? miny : y); // Track minimum vertical position
      } else if (c == 'R') {
        ++y; // Move right increases column index
        maxy = (maxy > y ? maxy : y); // Track maximum vertical position
      } else if (c == 'U') {
        --x; // Move up decreases row index
        minx = (minx < x ? minx : x); // Track minimum horizontal position
      } else if (c == 'D') {
        ++x; // Move down increases row index
        maxx = (maxx > x ? maxx : x); // Track maximum horizontal position
      }
      // Check if the robot would go out of bounds with current movement
      if (maxx >= n + minx) {
        minx += (x == minx); // Adjust start to avoid falling off board
        break;
      }
      if (maxy >= m + miny) {
        miny += (y == miny); // Adjust start to avoid falling off board
        break;
      }
    }
    std::cout << (1 - minx) << " " << (1 - miny) << std::endl; // Convert to 1-based indexing
  }
}


// https://github.com/VaHiX/codeForces/