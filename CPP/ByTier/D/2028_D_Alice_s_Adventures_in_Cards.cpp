/*
 * Problem URL : https://codeforces.com/contest/2028/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e5 + 10;

const string S = "qkj";

int n;

int p[5][maxn];

void solve() {
  cin >> n;
  for (int j = 1; j <= 3; j++) {
    for (int i = 1; i <= n; i++) {
      cin >> p[j][i];
    }
  }

  vector<int> Min(4, n);
  vector<pair<int, int>> dp(n + 10, {-1, -1}); // qkj, nxt_card

  for (int i = n - 1; i >= 1; i--) {
    int win = -1;
    for (int j = 1; j <= 3; j++) {
      if (p[j][i] > p[j][Min[j]])
        win = j;
    }
    if (win == -1)
      continue;
    dp[i] = {win, Min[win]};
    for (int j = 1; j <= 3; j++) {
      if (p[j][i] < p[j][Min[j]]) {
        Min[j] = i;
      }
    }
  }

  if (dp[1].first == -1) {
    cout << "NO\n";
    return;
  }

  cout << "YES\n";
  vector<pair<int, int>> ans = {dp[1]};
  while (ans.back().second >= 0) {
    ans.push_back(dp[ans.back().second]);
  }
  ans.pop_back();
  cout << ans.size() << "\n";
  for (auto p : ans) {
    cout << S[p.first - 1] << " " << p.second << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
