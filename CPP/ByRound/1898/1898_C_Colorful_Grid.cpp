// Problem: CF 1898 C - Colorful Grid
// https://codeforces.com/contest/1898/problem/C

/*
 * Problem: Colorful Grid
 * 
 * Purpose: To determine if it's possible to color the segments of an n x m grid 
 *          such that there exists a walk of length k+1 where no two consecutive 
 *          segments have the same color. If possible, output one valid coloring.
 * 
 * Algorithm:
 * - The minimum walk from (1,1) to (n,m) has length n + m - 2.
 * - Additional steps (k - minlen) must be even to allow alternating colors.
 * - The coloring strategy constructs a path, then modifies it to ensure 
 *   the constraints are met.
 * - Based on (k - minlen) % 4, we apply different coloring logic for horizontal 
 *   and vertical segments.
 * 
 * Time Complexity: O(n * m) per test case, as we iterate through grid segments once.
 * Space Complexity: O(n * m) for storing the grid coloring information.
 */
#include <cstdio>
#include <iosfwd>

using namespace std;
const int N = 18;
int t, n, m, k, a[N][N], b[N][N];
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &n, &m, &k);
    int minlen = n + m - 2;
    if (k < minlen || (k - minlen) % 2 == 1) {
      puts("NO");
      continue;
    }
    int now = 0;
    if ((k - minlen) % 4 == 2) {
      // Modified coloring for specific case where (k - minlen) % 4 == 2
      for (int j = 1; j < m; j++) {
        a[1][j] = now;
        now ^= 1; // Toggle color
      }
      for (int i = 1; i + 1 < n; i++) {
        b[i][m] = now;
        now ^= 1; // Toggle color
      }
      a[n][m - 1] = a[n - 1][m - 1] = now;
      b[n - 1][m] = b[n - 1][m - 1] = now ^ 1;
    } else {
      // Standard coloring for other cases
      for (int j = 1; j < m; j++) {
        a[1][j] = now;
        now ^= 1; // Toggle color
      }
      for (int i = 1; i < n; i++) {
        b[i][m] = now;
        now ^= 1; // Toggle color
      }
      b[n - 1][m - 1] = now ^ 1;
      a[n][m - 1] = a[n - 1][m - 1] = now;
    }
    puts("YES");
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < m; j++) {
        putchar(a[i][j] ? 'R' : 'B'); // Output 'R' or 'B'
        putchar(' ');
      }
      putchar('\n');
    }
    for (int i = 1; i < n; i++) {
      for (int j = 1; j <= m; j++) {
        putchar(b[i][j] ? 'R' : 'B'); // Output 'R' or 'B'
        putchar(' ');
      }
      putchar('\n');
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/