// Problem: CF 1986 B - Matrix Stabilization
// https://codeforces.com/contest/1986/problem/B

/*
B. Matrix Stabilization
Algorithms/Techniques: Simulation with neighbor comparisons
Time Complexity: O(n * m * k) where k is the number of iterations (bounded by 10^9 in practice)
Space Complexity: O(n * m) for storing the matrix

The algorithm simulates a stabilization process on a matrix:
- It finds the cell that is strictly greater than all its neighbors
- If such a cell exists, it reduces that cell's value by 1
- This repeats until no such cell exists
- Neighbors are defined as cells sharing a side (up, down, left, right)
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> v(n, std::vector<long>(m, 0));
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &v[row][col]);
      }
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        bool largest(true);
        long mx(0);
        // Check top neighbor
        if (row > 0 && v[row - 1][col] >= v[row][col]) {
          largest = false;
        } else if (row > 0) {
          mx = (mx > v[row - 1][col] ? mx : v[row - 1][col]);
        }
        // Check bottom neighbor
        if (row + 1 < n && v[row + 1][col] >= v[row][col]) {
          largest = false;
        } else if (row + 1 < n) {
          mx = (mx > v[row + 1][col] ? mx : v[row + 1][col]);
        }
        // Check left neighbor
        if (col > 0 && v[row][col - 1] >= v[row][col]) {
          largest = false;
        } else if (col > 0) {
          mx = (mx > v[row][col - 1] ? mx : v[row][col - 1]);
        }
        // Check right neighbor
        if (col + 1 < m && v[row][col + 1] >= v[row][col]) {
          largest = false;
        } else if (col + 1 < m) {
          mx = (mx > v[row][col + 1] ? mx : v[row][col + 1]);
        }
        // If current cell is the largest among neighbors, update it to max neighbor
        if (largest) {
          v[row][col] = mx;
        }
        printf("%ld ", v[row][col]);
      }
      puts("");
    }
  }
}


// https://github.com/VaHiX/codeForces/