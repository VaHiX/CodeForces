// Problem: CF 1842 C - Tenzing and Balls
// https://codeforces.com/contest/1842/problem/C

/*
Algorithm: Dynamic Programming with Prefix Tracking
Purpose: To find the maximum number of balls that can be removed by selecting pairs of same-colored balls,
         where the removal operation deletes a subarray between two equal elements.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm uses dynamic programming where:
- dp[i] represents the maximum number of balls that can be removed up to position i.
- minn[a[i]] keeps track of the best previous dp value for a given color,
  adjusted by the index difference to simulate optimal removal sequences.
*/

#include <algorithm>
#include <iostream>

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3, "Ofast", "inline")
using namespace std;
const int N = 2e5 + 1009;
int n, m, dp[N], minn[N], a[N];
void work() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= n; i++)
    minn[i] = -0x3f3f3f3f;  // Initialize minn with negative infinity
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    // dp[i] is the maximum removals up to i, considering either previous max or current segment
    dp[i] = max(dp[i - 1], i + minn[a[i]]);
    // Update minn for color a[i] with the best dp value minus (i-1)
    minn[a[i]] = max(minn[a[i]], dp[i - 1] - (i - 1));
    ans = max(ans, dp[i]);  // Track the global maximum
  }
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int Case = 1;
  cin >> Case;
  while (Case--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/