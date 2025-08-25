/*
 * Problem URL : https://codeforces.com/problemset/problem/2126/C
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k, height(0), time(0);
  cin >> n >> k;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  height = a[k - 1];
  sort(a.begin(), a.end());
  for (int x : a) {
    if (x > height) {
      time += x - height;
      if (time > height) {
        cout << "NO\n";
        return;
      }
      height = x;
    }
  }
  cout << "YES\n";
}

int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}
