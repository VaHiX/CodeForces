// Problem: CF 1662 M - Bottle Arrangements
// https://codeforces.com/contest/1662/problem/M

/*
 * Code Purpose:
 * This program determines whether it's possible to arrange a sequence of red (R) and white (W) wine bottles
 * such that each critic's request for a specific number of red and white wines in some contiguous interval
 * can be satisfied. It uses a greedy approach to construct the arrangement.
 *
 * Algorithms/Techniques:
 * - Greedy Algorithm: The core idea is to determine the minimum number of red and white wines needed
 *   to satisfy all critic requests by taking the maximum required for each type across all critics.
 * - Construction: Once we know the minimal required red and white wine counts (r and w), we construct
 *   a sequence of r reds followed by w whites if their sum equals n, otherwise it's impossible.
 *
 * Time Complexity: O(m) per test case, where m is the number of critics.
 * Space Complexity: O(1) — only using a fixed amount of extra space.
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
int best[11], t;
int main() {
  scanf("%d", &t);
  for (int CASE = 0; CASE < t; CASE++) {
    int n, m;
    scanf("%d%d", &n, &m);
    int r = 0, w = 0;
    // Read each critic's request and track the maximum required red and white wines
    for (int i = 0; i < m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      r = max(r, x);  // Track maximum red wine requirement
      w = max(w, y);  // Track maximum white wine requirement
    }
    // Adjust r to ensure we can cover all intervals (minimum r needed to satisfy all)
    r = max(r, n - w);
    // Check if a valid arrangement is possible
    if (r + w == n) {
      // Output r reds followed by w whites
      for (int i = 0; i < r; i++)
        printf("R");
      for (int i = 0; i < w; i++)
        printf("W");
      printf("\n");
    } else {
      printf("IMPOSSIBLE\n");
    }
  }
}


// https://github.com/VaHiX/CodeForces/