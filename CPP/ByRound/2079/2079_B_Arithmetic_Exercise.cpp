/*
 * Problem URL : https://codeforces.com/contest/2079/problem/B
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;

long long inf = 2e16 + 5;

void solve2() {
  int n, m;
  cin >> n >> m;
  vector<int> a(m);
  for (int &x : a)
    cin >> x;
  reverse(a.begin(), a.end());

  vector<vector<long long>> dp(m, vector<long long>(n + 5000, -inf));

  dp[0][1] = a[0];
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j <= i + 1; ++j) {
      if (j > n)
        continue;
      if (!((i + j) & 1))
        continue;
      if (j > 0)
        dp[i][j] = dp[i - 1][j - 1] + a[i];
      if (j < n)
        dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] - a[i]);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= m + 1; ++j) {
      if (dp[i][j] <= -inf + 2e12) {
        cout << "--- ";
        continue;
      }
      cout << dp[i][j] << " ";
    }
    cout << "\n";
  }

  cout << *max_element(dp[m - 1].begin(), dp[m - 1].end()) << "\n";
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<long long> a(m);
  for (long long &x : a)
    cin >> x;
  reverse(a.begin(), a.end());

  long long ans = a[0];

  multiset<long long> ms;
  for (int i = 1; i < m; ++i) {
    if (n % 2 == 0) {
      if (i & 1) {
        ans -= a[i];
        ms.insert(2 * a[i]);
      } else {
        if (!ms.size())
          ans += a[i];
        else
          ans = max(ans + a[i], ans + *ms.rbegin() - a[i]);
        ms.insert(2 * a[i]);
        if ((int)ms.size() > n / 2) {
          ms.erase(prev(ms.end()));
          ms.erase(ms.begin());
        } else {
          ms.erase(prev(ms.end()));
        }
      }
    } else {
      if (i & 1) {
        ans -= a[i];
        ms.insert(2 * a[i]);
        if ((int)ms.size() > n / 2)
          ms.erase(ms.begin());
      } else {
        if (!ms.size())
          ans += a[i];
        else
          ans = max(ans + a[i], ans + *ms.rbegin() - a[i]);
        ms.insert(2 * a[i]);
        ms.erase(prev(ms.end()));
      }
    }
  }

  long long mx = ans;
  vector<long long> gigachad;

  for (long long ass : ms)
    gigachad.push_back(ass);
  reverse(gigachad.begin(), gigachad.end());

  for (long long ass : gigachad) {
    ans += ass;
    mx = max(mx, ans);
  }

  cout << mx << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}
