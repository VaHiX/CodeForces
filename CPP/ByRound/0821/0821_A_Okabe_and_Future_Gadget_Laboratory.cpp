// Problem: CF 821 A - Okabe and Future Gadget Laboratory
// https://codeforces.com/contest/821/problem/A

/*
 * Problem: A. Okabe and Future Gadget Laboratory
 *
 * Task: Determine if a given n x n grid is "good".
 * A grid is good if every number not equal to 1 can be expressed as the sum
 * of a number in the same row and a number in the same column.
 *
 * Algorithm:
 * - For each cell (row, col) that is not 1:
 *   - Try all possible combinations of elements from the same row (a[row][y])
 *     and same column (a[x][col]) to see if their sum equals a[row][col].
 *   - If no such combination exists, the grid is not good.
 *
 * Time Complexity: O(n^4)
 *   - For each cell (n^2), we iterate over all rows and columns (n^2) to check sums.
 *
 * Space Complexity: O(n^2)
 *   - We store the grid of size n x n.
 */

#include <cstdio>
#include <vector>
int main() {
  int n;
  scanf("%d", &n);
  std::vector<std::vector<long>> a(n, std::vector<long>(n, 0));
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      scanf("%ld", &a[row][col]);
    }
  }
  bool possible(true);
  for (int row = 0; row < n; row++) {
    if (!possible) {
      break;
    }
    for (int col = 0; col < n; col++) {
      if (a[row][col] == 1) {
        continue;
      }
      bool current = false;
      for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
          if (a[row][col] == a[row][y] + a[x][col]) {
            current = true;
          }
        }
      }
      if (!current) {
        possible = false;
        break;
      }
    }
  }
  puts(possible ? "Yes" : "No");
  return 0;
}


// https://github.com/VaHiX/CodeForces/