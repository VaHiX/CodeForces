/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/C
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
#define fi first
#define se second
constexpr ll INF = 1e18;
ll work(int n, vector<vector<int>> &h, vector<int> &a) {
  vector<vector<ll>> dp(n, vector<ll>(2, INF));
  dp[0][0] = 0, dp[0][1] = a[0];
  for (int i = 1; i < n; i++) {
    for (int x = 0; x < 2; x++) {
      for (int y = 0; y < 2; y++) {
        bool flag = 1;
        for (int j = 0; j < n; j++)
          flag &= h[i - 1][j] + y != h[i][j] + x;
        if (flag) {
          if (x == 0)
            dp[i][x] = min(dp[i][x], dp[i - 1][y]);
          else
            dp[i][x] = min(dp[i][x], dp[i - 1][y] + a[i]);
        }
      }
    }
  }
  return min(dp[n - 1][0], dp[n - 1][1]);
}
void transpose(int n, vector<vector<int>> &h) {
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      swap(h[i][j], h[j][i]);
}
void solve() {
  int n;
  cin >> n;
  vector<vector<int>> h(n, vector<int>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> h[i][j];
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  ll ans = work(n, h, a);
  transpose(n, h);
  ans += work(n, h, b);
  if (ans >= INF)
    cout << "-1\n";
  else
    cout << ans << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
