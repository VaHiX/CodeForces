// Problem: CF 1456 A - Bouncing Ball
// https://codeforces.com/contest/1456/problem/A

/*
 * Problem: Bouncing Ball
 * Algorithms/Techniques: Dynamic Programming, Sliding Window
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n)
 *
 * The solution computes the minimum time to make a level passable,
 * where a ball must bounce from platform to platform every k steps
 * starting at position p. The allowed operations are:
 * - Adding a platform (cost x seconds)
 * - Removing the first cell (cost y seconds)
 *
 * Approach:
 * 1. Precompute for each position how many platforms are missing in
 *    a sequence starting from that position with step k.
 * 2. For each valid starting offset (0 to n-p), calculate cost of
 *    removing first i cells and filling remaining required platforms.
 */

#include <algorithm>
#include <cstdio>
const int N = 1e5 + 3;
int n, p, k, x, y, b[N], ans;
char a[N];
int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d%d%s%d%d", &n, &p, &k, a + 1, &x, &y);
    // Compute how many '0's (missing platforms) are in each sequence
    // starting from position i with step k
    for (int i = n; i; i--)
      b[i] = (i + k <= n ? b[i + k] : 0) + (a[i] == '0');
    ans = 0x3f3f3f3f;
    // Try all possible numbers of cells to remove from the front
    for (int i = 0; i <= n - p; i++)
      ans = std::min(ans, i * y + b[i + p] * x);
    printf("%d\n", ans);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/