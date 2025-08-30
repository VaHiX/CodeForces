/*
 * Problem URL : https://codeforces.com/problemset/problem/2060/G
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int kn = 2e5 + 25;
int n;
class ARR {
public:
  int x, y;
  bool operator<(const ARR &v) const {
    return (x < y ? x : y) < (v.x < v.y ? v.x : v.y);
  }
} a[kn];
int dp[kn][4];
inline void _solv() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = 0;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].x;
  for (int i = 1; i <= n; ++i)
    cin >> a[i].y;
  sort(a + 1, a + n + 1);
  dp[1][0] = dp[1][3] = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i].x > a[i - 1].x && a[i].y > a[i - 1].y) {
      dp[i][0] |= dp[i - 1][0];
      dp[i][1] |= dp[i - 1][3];
      dp[i][2] |= dp[i - 1][2];
      dp[i][3] |= dp[i - 1][1];
    }
    if (a[i].x > a[i - 1].y && a[i].y > a[i - 1].x) {
      dp[i][0] |= dp[i - 1][1];
      dp[i][1] |= dp[i - 1][2];
      dp[i][2] |= dp[i - 1][3];
      dp[i][3] |= dp[i - 1][0];
    }
  }
  printf((dp[n][0] | dp[n][1]) ? "YES\n" : "NO\n");
}
signed main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    _solv();
  return 0;
}
