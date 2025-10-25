// Problem: CF 1848 A - Vika and Her Friends
// https://codeforces.com/contest/1848/problem/A

/*
 * Problem: A. Vika and Her Friends
 * 
 * Purpose: Determine if Vika can escape from her friends forever in a grid-based mall.
 *          All girls move simultaneously each minute to adjacent rooms (Manhattan distance = 1).
 *          Vika wins if she never shares a room with any friend after any number of moves.
 * 
 * Algorithm:
 *   - Each cell on the grid has a "color" based on (x + y) % 2. This creates a checkerboard pattern.
 *   - If Vika and all friends are on cells of the same color, Vika can indefinitely avoid them by
 *     moving to different-colored cells, because each move keeps her on the opposite color.
 *   - If Vika is on one color and any friend is on the opposite color, then eventually the friend
 *     will catch up since they cannot change colors but must advance towards each other.
 * 
 * Time Complexity: O(k) per test case, where k is number of friends. We process each friend once.
 * Space Complexity: O(1), constant space used excluding input storage.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long a, b;
    scanf("%ld %ld", &a, &b);
    bool target = (a + b) % 2;  // Color of Vika's starting position
    bool ans(true);             // Assume Vika can escape initially
    for (long p = 0; p < k; p++) {
      long x, y;
      scanf("%ld %ld", &x, &y);
      bool cur = (x + y) % 2;   // Color of current friend's position
      if (cur == target) {
        ans = false;            // One friend is on the same color => Vika cannot escape
      }
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/