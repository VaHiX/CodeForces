// Problem: CF 812 A - Sagheer and Crossroads
// https://codeforces.com/contest/812/problem/A

/*
 * Problem: Sagheer and Crossroads
 * 
 * Purpose: Determine if an accident is possible at a traffic intersection,
 *          where an accident occurs if a pedestrian light and a lane light
 *          (for the same part or connected parts) are both green.
 * 
 * Algorithm:
 * - For each road part, check if the pedestrian light is green (p[u] = 1)
 * - If so, check if any of the lanes leading to or from that part are also green.
 * - Specifically, for part u, we check lanes from:
 *   - The same part (l[u], s[u], r[u])
 *   - The opposite part (s[(u + 2) % N] - straight from opposite part)
 *   - The next part in counter-clockwise direction (l[(u + 1) % N] - left from next part)
 *   - The previous part in counter-clockwise direction (r[(N + u - 1) % N] - right from previous part)
 * - If any of those are green, an accident is possible.
 * 
 * Time Complexity: O(1) - Fixed number of iterations (4 parts).
 * Space Complexity: O(1) - Only fixed-size arrays and variables used.
 */

#include <cstdio>
int main() {
  const int N = 4;
  int l[N], s[N], r[N], p[N];
  bool possible(0);  // Flag to track if any accident is possible
  for (int u = 0; u < N; u++) {
    scanf("%d %d %d %d", &l[u], &s[u], &r[u], &p[u]);  // Read lights for each part
  }
  for (int u = 0; u < N; u++) {
    // Check if pedestrian light is green and any relevant lane light is also green
    possible |= p[u] & (l[u] | s[u] | r[u] | s[(u + 2) % N] | l[(u + 1) % N] | r[(N + u - 1) % N]);
  }
  puts(possible ? "YES" : "NO");  // Output result
  return 0;
}


// https://github.com/VaHiX/CodeForces/