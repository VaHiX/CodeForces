/*
 * Problem URL : https://codeforces.com/problemset/problem/2067/F
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;
int arr[N], n, t;
unordered_map<int, int> dp;
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    dp.clear();
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
      cin >> arr[i];
      arr[i] ^= arr[i - 1];
      dp[arr[i - 1]] = 3 * dp[arr[i - 1]] + 2 * dp[arr[i]];
      dp[arr[i - 1]] %= mod;
    }
    int ans = 0;
    for (auto e : dp) {
      ans += e.second;
      ans %= mod;
    }
    cout << ans << "\n";
  }
  return 0;
}