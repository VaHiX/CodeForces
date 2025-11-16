// Problem: CF 1881 C - Perfect Square
// https://codeforces.com/contest/1881/problem/C

/*
C. Perfect Square

Purpose:
This code finds the minimum number of character changes needed to make an n×n matrix a perfect square,
where a perfect square matrix remains unchanged after a 90-degree clockwise rotation.

Algorithm:
- For each group of four symmetric positions under 90° rotation, we find the maximum character among them.
- Then we update all four positions to this maximum character.
- The number of operations is the sum of differences between the current and new characters for each position in the group.

Time Complexity: O(n^2) per test case
Space Complexity: O(n^2) for storing the matrix

Techniques:
- Matrix rotation symmetry
- Greedy approach: minimize operations by choosing maximum character in each symmetric group
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::vector<std::string> m(n);
    for (long row = 0; row < n; row++) {
      std::cin >> m[row];
    }
    long cnt(0);
    // Iterate through the top-left quarter of the matrix
    for (long row = 0; row < n / 2; row++) {
      for (long col = 0; col < (n + 1) / 2; col++) {
        // Extract characters at four symmetric positions
        char w = m[row][col]; // Top-left
        char x = m[col][n - 1 - row]; // Top-right
        char y = m[n - 1 - row][n - 1 - col]; // Bottom-right
        char z = m[n - 1 - col][row]; // Bottom-left

        // Find the maximum character among the four
        char f(w > x ? w : x);
        f = (f > y ? f : y);
        f = (f > z ? f : z);

        // Update all four positions to the maximum character
        m[row][col] = m[col][n - 1 - row] = m[n - 1 - row][n - 1 - col] =
            m[n - 1 - col][row] = f;

        // Count the number of operations needed for this group
        cnt += (f - w) + (f - x) + (f - y) + (f - z);
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/