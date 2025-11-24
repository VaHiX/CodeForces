// Problem: CF 1427 C - The Hard Work of Paparazzi
// https://codeforces.com/contest/1427/problem/C

/*
C. The Hard Work of Paparazzi
Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n^2) 
Space Complexity: O(n)

The problem involves finding the maximum number of celebrities a paparazzi can photograph
in Manhattan given their positions and times, starting from position (1, 1).
We use dynamic programming where f[i] represents the maximum number of celebrities
that can be photographed ending at celebrity i. The constraint is that to reach
celebrity i from celebrity j, the travel time must be less than or equal to 
the difference in their times.

The optimization uses maxn array to avoid redundant checks and improve performance.
*/
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int r, n, x[100010], y[100010], t[100010], f[100010], maxn[100010], ans = 0;
int main() {
  scanf("%d%d", &r, &n);
  for (int i = 1; i <= n; i++)
    scanf("%d%d%d", &t[i], &x[i], &y[i]), f[i] = -1;
  x[0] = y[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      if (f[j] >= 0 && abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j])
        f[i] = max(f[i], f[j] + 1);
      if (f[i] >= maxn[j] + 1)
        break;
    }
    ans = max(ans, f[i]);
    maxn[i] = max(maxn[i - 1], f[i]);
  }
  printf("%d\n", ans);
}


// https://github.com/VaHiX/codeForces/