// Problem: CF 2094 F - Trulimero Trulicina
// https://codeforces.com/contest/2094/problem/F

/*
 * Problem: F. Trulimero Trulicina
 * Purpose: Generate an n x m grid of integers from 1 to k such that:
 *   - Each integer appears exactly (n*m)/k times
 *   - No two adjacent cells have the same integer
 *   - All values are in range [1, k]
 *
 * Algorithm:
 *   - Fill grid using a pattern based on `(row * m + col) % k` to distribute values.
 *   - Use a shift flag to alternate row parity when m is divisible by k,
 *     ensuring no adjacent cells share same value.
 *
 * Time Complexity: O(n * m) per test case
 * Space Complexity: O(n * m) for output grid
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    bool shift = ((m % k) == 0); // Determine if shift is needed for parity
    std::vector<std::vector<long>> f(n, std::vector<long>(m, 0)); // Initialize grid
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        long x = (row * m + col) % k; // Base value based on position
        f[row][col] = 1 + ((shift * row % 2) + x) % k; // Apply shift and wrap around
      }
    }
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        printf("%ld ", f[row][col]);
      }
      puts(""); // Newline after each row
    }
  }
}


// https://github.com/VaHiX/codeForces/