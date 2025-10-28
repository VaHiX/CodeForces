// Problem: CF 1866 I - Imagination Castle
// https://codeforces.com/contest/1866/problem/I

/*
 * Problem: Imagination Castle
 * 
 * Purpose: Determine the winner of a game played on an N×M chessboard where a special piece (castle) moves only right or down.
 *          The game ends when a player moves to a special tile (win), or if no move is possible (current player loses).
 *          Players alternate turns, starting with Chaneka.
 *
 * Algorithm:
 * - Preprocess special tiles by recording the maximum column for each row and maximum row for each column.
 * - Simulate backward from (N,M) toward (1,1), checking if a position can reach (1,1) without landing on a special tile.
 * - If such a path exists, Chaneka wins; otherwise, Bhinneka wins.
 *
 * Time Complexity: O(N + M + K)
 * Space Complexity: O(N + M)
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
int n, m, k, px, py, x[200005], y[200005], xx[200005], yy[200005];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d %d", &x[i], &y[i]); // Read special tile positions
    xx[x[i]] = max(xx[x[i]], y[i]); // Store max column for each row
    yy[y[i]] = max(yy[y[i]], x[i]); // Store max row for each column
  }
  if (n == 1 && m == 1) {
    puts("Bhinneka"); // Trivial case: already at final position and no special tile at (1,1)
    return 0;
  }
  px = n; // Start from bottom-right corner
  py = m;
  while (px > 1 && py > 1) {
    --px; // Move up
    --py; // Move left
    while (1) {
      if (px >= 1 && xx[px] > py) { // If a special tile in this row is to the right of current position
        --px; // Move further up
        continue;
      }
      if (py >= 1 && yy[py] > px) { // If a special tile in this column is below current position
        --py; // Move further left
        continue;
      }
      break; // No more obstacles, proceed
    }
    if (px == 1 && py == 1) {
      puts("Bhinneka"); // Found path to start with no obstacle
      return 0;
    }
  }
  puts("Chaneka"); // No valid path exists, so second player (Chaneka) wins
  return 0;
}


// https://github.com/VaHiX/codeForces/