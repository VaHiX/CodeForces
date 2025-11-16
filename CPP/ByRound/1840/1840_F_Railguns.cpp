// Problem: CF 1840 F - Railguns
// https://codeforces.com/contest/1840/problem/F

/*
Purpose: This code solves the problem of finding the minimum time for a character to reach from (0,0) to (n,m) on a grid 
         while avoiding railgun shots. It uses dynamic programming with preprocessing of shots to determine safe paths.

Algorithms/Techniques:
- Dynamic Programming (DP) with state dp[i][j] representing the minimum time to reach position (i,j)
- Preprocessing shots by time and applying them to mark unsafe positions
- Greedy approach to update DP states efficiently

Time Complexity: O(r * n * m) where r is the number of shots, n and m are dimensions of the grid.
Space Complexity: O(n * m + r) for the DP table and storing shots.
*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int N = 105;
vector<vector<int>> dp;
int shot[N][3];
int cmp(const void *p, const void *q) {
  int *a = (int *)p;
  int *b = (int *)q;
  return a[0] - b[0];
}
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int T, n, m, r;
  cin >> T;
  while (T--) {
    cin >> n >> m >> r;
    for (int i = 0; i < r; i++)
      cin >> shot[i][0] >> shot[i][1] >> shot[i][2];
    qsort(shot, r, sizeof(shot[0]), cmp);
    dp.resize(n + 1, vector<int>(m + 1));
    dp.assign(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;
    bool reachable = false;
    int t = 0;
    int clost = m + n;
    int i = 0, j;
    for (; i < r; i++) {
      // Check if we can reach destination before next shot
      if (t + clost < shot[i][0]) {
        reachable = true;
        break;
      }
      // Update DP table for all current reachable positions
      for (j = 0; j <= n; j++) {
        for (int k = 0; k <= m; k++) {
          if (dp[j][k] != -1) {
            // Vertical moves (rightward)
            for (int s = 1; j + s <= n && dp[j][k] + s <= shot[i][0]; s++) {
              if (dp[j + s][k] != -1 && dp[j][k] + s >= dp[j + s][k])
                break;
              dp[j + s][k] = dp[j][k] + s;
            }
            // Horizontal moves (upward)
            for (int s = 1; k + s <= m && dp[j][k] + s <= shot[i][0]; s++) {
              if (dp[j][k + s] != -1 && dp[j][k] + s >= dp[j][k + s])
                break;
              dp[j][k + s] = dp[j][k] + s;
            }
          }
        }
      }
      // Apply all shots that occur at the same time
      for (j = i; j < r; j++) {
        if (shot[j][0] != shot[i][0])
          break;
        if (shot[j][1] == 1) {
          // Horizontal shot: mark entire row as unsafe
          for (int k = 0; k <= m; k++) {
            dp[shot[j][2]][k] = -1;
          }
        } else {
          // Vertical shot: mark entire column as unsafe
          for (int k = 0; k <= n; k++) {
            dp[k][shot[j][2]] = -1;
          }
        }
      }
      // Check if destination is reachable after applying shots
      if (dp[n][m] != -1) {
        reachable = true;
        break;
      }
      t = shot[i][0];
      i = j - 1;
      clost = m + n;
      int cnt = 0;
      // Update DP with current time
      for (j = 0; j <= n; j++) {
        for (int k = 0; k <= m; k++) {
          if (dp[j][k] != -1) {
            cnt++;
            dp[j][k] = shot[i][0];
            if (n - j + m - k < clost) {
              clost = n - j + m - k;
            }
          }
        }
      }
      if (cnt == 0)
        break;
    }
    // Output result based on what happened during loop
    if (i == r || reachable)
      cout << t + clost << endl;
    else
      cout << -1 << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/