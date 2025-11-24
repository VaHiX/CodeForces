// Problem: CF 1371 D - Grid-00100
// https://codeforces.com/contest/1371/problem/D

/*
 * Problem: Grid Construction to Minimize f(A) = (max(R)-min(R))^2 + (max(C)-min(C))^2
 * Algorithm: Greedily place 1s in a diagonal-like pattern to balance row and column sums.
 * Time Complexity: O(n^2) per test case (due to grid construction and output)
 * Space Complexity: O(n^2) for the grid storage
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  long t;
  std::cin >> t;
  while (t--) {
    long n, k;
    std::cin >> n >> k;
    std::string s(n, '0');               // Create a string of n '0's
    std::vector<std::string> v(n, s);    // Create an n x n grid filled with '0'
    long row(0), col(0);                 // Starting position for placing 1s
    
    // Place k ones in the grid in a way to minimize f(A)
    for (long p = 0; p < k; p++) {
      v[row][col] = '1';                 // Place 1 at current position
      row = (row + 1) % n;               // Move down (wrap around if needed)
      col = (col + 1 + (row == 0)) % n;  // Move right, with special case for wrap-around
    }
    
    // Output the minimum possible value of f(A)
    std::cout << (k % n ? 2 : 0) << std::endl;
    
    // Print the constructed grid
    for (long p = 0; p < n; p++) {
      std::cout << v[p] << std::endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/