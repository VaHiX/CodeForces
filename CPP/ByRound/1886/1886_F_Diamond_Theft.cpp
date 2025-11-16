// Problem: CF 1886 F - Diamond Theft
// https://codeforces.com/contest/1886/problem/F

/*
Algorithm/Techniques: Binary search on answer + greedy + prefix sum
Time Complexity: O(n^2 * log n) where n is the number of cameras
Space Complexity: O(n) for storing camera data and auxiliary arrays

This problem uses binary search on the time to find the minimum time needed 
to steal both diamonds. For each candidate time, a greedy approach is used to 
check if it's possible to disable cameras such that both diamonds can be stolen.
The solution maintains a prefix sum array to efficiently determine how many 
cameras are active at any given time. The algorithm sorts the cameras monitoring 
both diamonds and uses a sliding window approach for optimization.
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define Fu(i, a, b) for (register int i = a; i <= b; i++)
using namespace std;
int n, s, t, g[4][1505], cnt[3005], mx, ans = 0x7fffffff;
int bj[1505], z[1505];
void solve(int t) {
  memset(cnt, 0, sizeof(cnt));
  memset(bj, 0, sizeof(bj));
  Fu(i, 1, g[1][0]) cnt[g[1][i]]++; // Mark positions where first diamond cameras are active
  Fu(i, 1, g[3][0]) cnt[max(0, g[3][i] - t - 1)]++; // Mark positions where both diamonds cameras are active, adjusted by time t
  int o = 1, top = 0, tmp = 0;
  Fu(i, 0, mx) {
    if (i)
      cnt[i] += cnt[i - 1]; // Prefix sum to compute number of active cameras at time i
    while (o <= g[3][0] && g[3][o] - t - 1 <= i)
      z[++top] = o++; // Use a stack to track which cameras need to be disabled
    while (top && cnt[i] > i) // If there are more active cameras than allowed, disable some
      cnt[i]--, cnt[g[3][z[top]]]++, bj[z[top--]] = 1, tmp++; // Disabling a camera
    if (cnt[i] > i)
      return; // Impossible to satisfy constraints at time i
  }
  memset(cnt, 0, sizeof(cnt));
  cnt[t + 1]++; // Start point for stealing first diamond
  Fu(i, 1, g[1][0]) cnt[min(mx, g[1][i] + t + 1)]++; // Add first diamond cameras, adjusted by time t
  Fu(i, 1, g[2][0]) cnt[g[2][i]]++; // Add second diamond cameras
  Fu(i, 1, g[3][0]) {
    cnt[g[3][i]]++; // Add both diamond cameras
    if (bj[i]) // If this camera was disabled earlier, account for its effect
      cnt[min(mx, g[3][i] + t + 1)]++;
  }
  Fu(i, 0, mx) {
    if (i)
      cnt[i] += cnt[i - 1]; // Recompute prefix sum
    if (cnt[i] > i)
      return; // Again, impossible if more cameras active than slots
  }
  ans = min(ans, tmp); // Update minimum number of hacks needed
}
int main() {
  scanf("%d", &n), mx = (n << 1) + 2; // mx is an upper bound for time calculation
  Fu(i, 1, n) scanf("%d%d", &s, &t), g[s][++g[s][0]] = t; // Categorize cameras by type
  sort(g[3] + 1, g[3] + g[3][0] + 1); // Sort cameras monitoring both diamonds
  Fu(i, 0, n) solve(i); // Try all times from 0 to n
  if (ans > n)
    printf("-1");
  else
    printf("%d", ans + n + 2); // Final result includes base time and cost
  return 0;
}


// https://github.com/VaHiX/CodeForces/