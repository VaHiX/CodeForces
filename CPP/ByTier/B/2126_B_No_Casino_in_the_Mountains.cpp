/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/B
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k, r(0), c(0), x;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> x;
    if (x)
      c = 0;
    else
      c++;
    if (c == k) {
      r++;
      c = 0;
      if (i < n - 1) {
        cin >> x;
        i++;
      }
    }
  }
  cout << r << "\n";
}

int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
