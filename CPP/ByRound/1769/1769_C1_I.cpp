// Problem: CF 1769 C1 - Подкрутка I
// https://codeforces.com/contest/1769/problem/C1

/*
 * Problem: C1. Подкрутка I
 * Algorithm: Dynamic Programming with State Compression
 * Time Complexity: O(n^2) where n <= 50
 * Space Complexity: O(n^2) due to dp table
 *
 * The problem asks to find the maximum length of a continuous interval
 * where each day has at least one commit, after optimally shifting commits
 * forward by at most 1 day.
 *
 * Approach:
 * - For each commit, we can place it either in its original day or day+1
 * - We use dynamic programming where dp[i][d] represents the maximum
 *   length of continuous days starting from day d, considering commits
 *   from index i to the end
 * - We build the DP table backwards and try both possibilities for
 *   placing each commit (at original day or day+1)
 */

#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1e5 + 10;
int a[N];
int dp[1007][1007];
int main() {
  int n;
  cin >> n;
  while (n--) {
    int len, ans = 1;
    cin >> len;
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= len; i++) {
      cin >> a[i];
      dp[i][a[i]] = 1;
      dp[i][a[i] + 1] = 1;
    }
    for (int i = len - 1; i >= 1; i--) {
      // For commit at day a[i], we can place it either at a[i] or a[i]+1
      // The state transition considers the best continuation from later commits
      dp[i][a[i]] = max(dp[i + 1][a[i] + 1] + 1, dp[i + 1][a[i]]);
      dp[i][a[i] + 1] = max(dp[i + 1][a[i] + 2] + 1, dp[i + 1][a[i] + 1]);
      ans = max(max(dp[i][a[i]], dp[i][a[i] + 1]), ans);
    }
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/