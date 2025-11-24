// Problem: CF 1075 A - The King's Race
// https://codeforces.com/contest/1075/problem/A

#include <cstdio>
typedef long long ll;

/*
 * Problem: A. The King's Race
 *
 * Purpose:
 *   Determine which king (white or black) will reach a given cell (x, y)
 *   first on an n x n chessboard, where the white king starts at (1, 1)
 *   and the black king starts at (n, n). Kings move optimally.
 *
 * Algorithms/Techniques:
 *   - Calculate Manhattan-like distances from each king's starting position
 *     to the target cell (x, y), considering that kings can move diagonally.
 *   - The distance is calculated as the minimum number of moves needed,
 *     which equals the maximum of row and column differences.
 *   - Compare these distances to determine which king reaches first.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

int main() {
  ll n;
  scanf("%lld", &n);
  ll x, y;
  scanf("%lld %lld", &x, &y);

  // Distance from white king (1,1) to (x,y) in terms of maximum of row/column offset
  ll dw = (x - 1) > (y - 1) ? (x - 1) : (y - 1);

  // Distance from black king (n,n) to (x,y)
  ll db = (n - x) > (n - y) ? (n - x) : (n - y);

  // Output winner: if white king's distance is less than or equal to black,
  // then white wins (as it moves first); otherwise black wins
  puts((dw <= db) ? "White" : "Black");
  return 0;
}

// https://github.com/VaHiX/codeForces/