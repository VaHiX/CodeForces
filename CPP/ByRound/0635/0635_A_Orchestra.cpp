// Problem: CF 635 A - Orchestra
// https://codeforces.com/contest/635/problem/A

/*
 * Problem: Orchestra
 * 
 * Purpose: Count the number of axis-parallel rectangles that can be formed 
 *          in an r x c grid such that they contain at least k violas.
 * 
 * Algorithm: 
 *   1. Read the grid dimensions (r, c) and number of violas (n).
 *   2. Mark the positions of violas in a 2D array.
 *   3. Iterate through all possible rectangles defined by top-left (i,j) and bottom-right (k,l) corners.
 *   4. For each rectangle, count the number of violas inside it by checking the grid.
 *   5. If count >= k, increment the answer.
 * 
 * Time Complexity: O(r^2 * c^2 * r * c) = O(r^3 * c^3)
 *   - Outer loops iterate over all possible top-left corners (r * c)
 *   - Inner loops iterate over all possible bottom-right corners (r * c)
 *   - Innermost loops count violas in the rectangle (r * c)
 * 
 * Space Complexity: O(r * c)
 *   - 2D array to store viola positions
 * 
 * Techniques: Brute force over all possible rectangles
 */

#include <iostream>

using namespace std;
typedef long long ll;
int a[15][15]; // Grid to mark viola positions (1 if viola, 0 otherwise)
int main() {
  int r, c, n, tt, x, y, ans = 0;
  cin >> r >> c >> n >> tt;
  // Mark viola positions in the grid
  for (int i = 1; i <= n; i++) {
    cin >> x >> y;
    a[x][y] = 1;
  }
  // Iterate over all possible rectangles
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= c; j++)
      for (int k = i; k <= r; k++)
        for (int l = j; l <= c; l++) {
          int cnt = 0;
          // Count violas in current rectangle
          for (int p = i; p <= k; p++)
            for (int q = j; q <= l; q++)
              if (a[p][q])
                cnt++;
          // If at least tt violas, increment answer
          if (cnt >= tt)
            ans++;
        }
  cout << ans;
  return 0;
}


// https://github.com/VaHiX/CodeForces/