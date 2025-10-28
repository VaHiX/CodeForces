// Problem: CF 1720 C - Corners
// https://codeforces.com/contest/1720/problem/C

/*
C. Corners
Time Complexity: O(n * m) per test case
Space Complexity: O(n * m) for the matrix storage

Algorithm:
- For each 2x2 submatrix, check if it forms a valid L-shape with at least one '1'.
- An L-shape is defined as a 2x2 square with one corner removed.
- We can perform operations on such L-shapes to reduce them to all zeros.
- The key insight is that we want to maximize the number of such operations:
  - If there are no ones, answer is 0.
  - Otherwise, for each valid 2x2 submatrix, we count how many ones it contains.
  - We use greedy approach: for each 2x2 block with at least one '1', we consider
    the number of operations that can be done depending on how many '1's are in it.
    - If a 2x2 block has exactly 1 or 2 '1's, we perform 1 operation (minimum).
    - If more than 2 '1's, we can do at most (count - 1) operations.
  - However, the code uses a simplified logic:
    - For each valid L-shape, count '1's in it.
    - If it has more than 2 ones, then it contributes (count - 1) operations.
    - If it has 1 or 2 ones, it contributes 1 operation.
    - But we are trying to minimize the worst-case scenario and get maximum total,
      so the value is calculated as (ones - min_operations).
*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::vector<std::string> v(n);
    for (long row = 0; row < n; row++) {
      std::cin >> v[row];
    }
    long ones(0);
    for (long row = 0; row < n; row++) {
      for (long col = 0; col < m; col++) {
        ones += v[row][col] - '0'; // Count total number of '1's
      }
    }
    long mn(5); // Initialize to large value to find minimum later
    for (long row = 0; row < n - 1; row++) {
      for (long col = 0; col < m - 1; col++) {
        // Calculate number of '1's in the 2x2 submatrix starting at (row, col)
        long cur = v[row][col] + v[row][col + 1] + v[row + 1][col] +
                   v[row + 1][col + 1] - 4 * '0';
        if (!cur) {
          continue; // Skip blocks with no '1's
        }
        // Determine number of operations possible for this L-shape
        long tst = (cur > 2) ? (cur - 1) : 1;
        mn = (mn < tst) ? mn : tst; // Keep track of minimum possible operations per block
      }
    }
    // Final answer is total '1's minus the minimum operations needed from best L-shapes
    long ans = ones ? (1 + ones - mn) : 0;
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/