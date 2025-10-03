// Problem: CF 2069 B - Set of Strangers
// https://codeforces.com/contest/2069/problem/B

/*
B. Set of Strangers
Purpose: 
  Given a grid of colors, determine the minimum number of steps to make the entire grid the same color.
  Each step allows selecting a set of "strangers" (non-adjacent cells) that all have the same color,
  and paint them with a new color.

Algorithms/Techniques:
  - Use Union-Find or set-based techniques to identify connected components and avoid double-counting
  - Process grid to count unique colors and adjacent same-color pairs

Time Complexity: O(n * m)
Space Complexity: O(n * m)

*/

#include <cstdio>
#include <unordered_set>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<std::vector<long>> f(n, std::vector<long>(m, 0));
    std::unordered_set<long> sa, sb; // sa: all unique colors, sb: colors that appear in adjacent cells
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        scanf("%ld", &f[row][col]);
        sa.insert(f[row][col]); // Add current color to set of all colors
        if (row && f[row - 1][col] == f[row][col]) {
          // If above cell has same color, add it to adjacent set
          sb.insert(f[row][col]);
        }
        if (col && f[row][col - 1] == f[row][col]) {
          // If left cell has same color, add it to adjacent set
          sb.insert(f[row][col]);
        }
      }
    }
    // Result is unique colors minus shared colors plus one edge case adjustment
    printf("%ld\n", sa.size() + sb.size() - (sb.size() > 0) - 1);
  }
}


// https://github.com/VaHiX/codeForces/