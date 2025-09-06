/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, r(10);
  cin >> n;
  while (n > 0) {
    if ((n % 10) < r)
      r = n % 10;
    n /= 10;
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
