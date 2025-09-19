/*
 * Problem URL : https://codeforces.com/contest/2008/problem/H
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void solve() {
  int n, q;
  cin >> n >> q;

  int cnt[n + 1]{0};
  for (int i = 0, x; i < n; i++)
    cin >> x, cnt[x]++;
  for (int i = 1; i <= n; i++)
    cnt[i] += cnt[i - 1];

  int ans[n + 1]{0};
  for (int x = 1; x <= n; x++) {
    int l = 0, r = x, val = r;
    while (l <= r) {
      int m = (l + r) >> 1, c;
      c = cnt[m];

      for (int i = 1; i * x <= n; i++)
        c += cnt[min(n, i * x + m)] - cnt[i * x - 1];

      if (c - 1 >= n / 2)
        r = m - 1, val = m;
      else
        l = m + 1;
    }
    ans[x] = val;
  }

  while (q--) {
    int x;
    cin >> x;
    cout << ans[x] << ' ';
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int T = 1;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    // cout << "Case " << i << ": ";
    solve();
  }
}