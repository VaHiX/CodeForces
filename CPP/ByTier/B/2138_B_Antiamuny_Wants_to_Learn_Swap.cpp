/*
 * Problem URL : https://codeforces.com/contest/2138/problem/B
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n + 2);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  vector<int> mxl(n + 1), mir(n + 1);
  for (int i = 1; i <= n; i++) {
    mxl[i] = i - 1;
    while (mxl[i] > 0 && a[mxl[i]] < a[i])
      mxl[i] = mxl[mxl[i]];
  }
  for (int i = n; i >= 1; i--) {
    mir[i] = i + 1;
    while (mir[i] <= n && a[mir[i]] > a[i])
      mir[i] = mir[mir[i]];
  }
  vector<int> L(n + 1, 0);
  for (int i = 2; i < n; i++) {
    if (mxl[i] > 0 && mir[i] <= n) {
      L[mir[i]] = max(L[mir[i]], mxl[i]);
    }
  }
  for (int i = 1; i <= n; i++) {
    L[i] = max(L[i], L[i - 1]);
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    if (l <= L[r])
      cout << "NO\n";
    else
      cout << "YES\n";
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}