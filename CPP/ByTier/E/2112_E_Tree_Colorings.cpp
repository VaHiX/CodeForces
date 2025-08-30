/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/E
 * Submit Date : 2025-08-17
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/E
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 5, v = 5e5;
int dp[maxn];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  for (int i = 1; i <= v; ++i)
    dp[i] = 1e9;
  dp[1] = 1;
  for (int i = 3; i <= v; ++i) {
    for (int j = i; j <= v; j += i) {
      dp[j] = min(dp[j], dp[i - 2] + dp[j / i]);
    }
  }
  int t;
  cin >> t;
  int m;
  while (t--) {
    cin >> m;
    if (dp[m] == 1e9)
      cout << "-1\n";
    else
      cout << dp[m] << "\n";
  }
  return 0;
}