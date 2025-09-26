/*
 * Problem URL : https://codeforces.com/contest/1251/problem/D
 * Submit Date : 2025-09-05
 */

#pragma GCC optimize("O2")
#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007LL
#define eps 1e-8

using namespace std;

int main() {
  cin.tie(0), ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    ll s;
    cin >> n >> s;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
      cin >> a[i] >> b[i], s -= a[i];
    ll l = *min_element(a.begin(), a.end()),
       r = *max_element(b.begin(), b.end()), m;
    while (l < r) {
      m = (l + r + 1) >> 1;
      vector<ll> tmp;
      int c = n / 2 + 1;
      for (int i = 0; i < n; i++) {
        if (a[i] < m && b[i] >= m)
          tmp.push_back(m - a[i]);
        else if (a[i] >= m)
          c--;
      }
      sort(tmp.begin(), tmp.end());
      if (c <= 0 || (tmp.size() >= c &&
                     accumulate(tmp.begin(), tmp.begin() + c, 0ll) <= s))
        l = m;
      else
        r = m - 1;
    }
    cout << l << "\n";
  }
  return 0;
}
