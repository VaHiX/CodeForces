// Problem: CF 509 A - Maximum in Table
// https://codeforces.com/contest/509/problem/A

/*
 * Code Purpose:
 * This program computes the maximum value in an n×n table where:
 * - First row and first column are all 1s.
 * - Each remaining cell is the sum of the cell above and the cell to the left.
 * 
 * The table essentially represents a Pascal's triangle variant, but with a different initialization.
 * 
 * Algorithm/Techniques:
 * - Dynamic Programming with space optimization
 * - Uses a 1D vector to simulate the 2D table, updating values in a single pass
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */

#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d\n", &n);
  std::vector<long long> a(n, 1);  // Initialize all elements to 1
  for (int p = 1; p < n; p++) {    // Iterate through rows starting from second
    for (int q = 1; q < n; q++) {  // Iterate through columns starting from second
      a[q] += a[q - 1];            // Update current cell with sum of left cell (a[q-1])
    }
  }
  printf("%lld\n", a[n - 1]);      // Print the maximum value in the last column
  return 0;
}


// https://github.com/VaHiX/CodeForces/