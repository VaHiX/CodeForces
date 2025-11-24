// Problem: CF 1996 B - Scale
// https://codeforces.com/contest/1996/problem/B

/*
Scale
Algorithms/Techniques: Grid traversal, block processing
Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) for the input grid and result grid

Given a square grid of 0s and 1s, reduce it by a factor k by grouping cells into k×k blocks,
and replacing each block with a single cell having the value of all cells in that block.
The problem guarantees that each k×k block contains uniform values.
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::vector<std::string> v(n);
    for (long p = 0; p < n; p++) {
      std::cin >> v[p];
    }
    // Create a new grid of size n/k x n/k
    std::vector<std::string> w(n / k, std::string(n / k, '0'));
    for (long row = 0; row < n; row += k) {
      for (long col = 0; col < n; col += k) {
        // Take the top-left cell of each k×k block as representative
        w[row / k][col / k] = v[row][col];
      }
    }
    for (long p = 0; p < w.size(); p++) {
      std::cout << w[p] << std::endl;
    }
  }
}


// https://github.com/VaHiX/codeForces/