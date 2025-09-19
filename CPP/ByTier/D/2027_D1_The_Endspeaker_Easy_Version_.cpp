/*
 * Problem URL : https://codeforces.com/contest/2027/problem/D1
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef unordered_map<ll, vl> mlv;
typedef unordered_map<ll, bool> mlb;
const ll infll = 1e18;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    vl a(n + 1), pre(n + 1);
    ll max_a = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      max_a = max(max_a, a[i]);
      pre[i] = pre[i - 1] + a[i];
    }
    vl b(m + 1);
    for (int i = 1; i <= m; i++)
      cin >> b[i];
    if (max_a > b[1]) {
      cout << "-1\n";
      continue;
    }
    vl dp(n + 1, infll);
    dp[0] = 0;
    for (int j = 1; j <= m; j++) {
      int l = 0, r = 1;
      while (r <= n) {
        while (l < r && pre[r] - pre[l] > b[j])
          l++;
        if (l < r)
          dp[r] = min(dp[r], dp[l] + m - j);
        r++;
      }
    }
    cout << dp[n] << "\n";
  }
  return 0;
}