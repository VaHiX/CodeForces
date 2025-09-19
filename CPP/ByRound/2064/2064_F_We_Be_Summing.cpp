/*
 * Problem URL : https://codeforces.com/problemset/problem/2064/F
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int mxN = 2e5;
int t, n, k, a[mxN], l[mxN], r[mxN], mnb[mxN], mxb[mxN];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> t;
  while (t--) {
    cin >> n >> k, k -= 2;
    for (int i = 0; i < n; ++i) {
      cin >> a[i], --a[i];
      l[i] = i - 1;
      while (~l[i] && a[l[i]] > a[i])
        l[i] = l[l[i]];
    }
    for (int i = n - 1; ~i; --i) {
      r[i] = i + 1;
      while (r[i] < n && a[r[i]] < a[i])
        r[i] = r[r[i]];
    }
    memset(mnb, 0, 4 * n);
    memset(mxb, 0, 4 * n);
    ll ans = 0;
    auto addmn = [&](int i, int x) {
      mnb[i] += x;
      if (0 <= k - i && k - i < n)
        ans += (ll)x * mxb[k - i];
    };
    auto addmx = [&](int i, int x) {
      mxb[i] += x;
      if (0 <= k - i && k - i < n)
        ans += (ll)x * mnb[k - i];
    };
    vector<ar<int, 4>> rs;
    {
      int i = 0;
      while (i < n) {
        addmx(a[i], r[i] - i);
        i = r[i];
      }
    }
    for (int i = 0; i < n - 1; ++i) {
      int j1 = i - 1;
      while (~j1 && a[j1] > a[i]) {
        mnb[a[j1]] -= j1 - l[j1];
        j1 = l[j1];
      }
      mxb[a[i]] -= r[i] - i;
      addmn(a[i], i - j1);
      int j2 = i + 1;
      while (j2 < n && a[j2] < a[i]) {
        addmx(a[j2], r[j2] - j2);
        j2 = r[j2];
      }
    }
    cout << ans << "\n";
  }
}