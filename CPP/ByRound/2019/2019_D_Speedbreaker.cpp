/*
 * Problem URL : https://codeforces.com/contest/2019/problem/D
 * Submit Date : 2025-09-11
 */


#include <bits/stdc++.h>
using namespace std;
#define per(i, r, l) for (int i = r; i >= l; i--)

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a)
    cin >> x;
  int l = 0, r = n - 1;
  int L = 0, R = n - 1;
  per(t, n, 1) {
    while (l < n && a[l] > t)
      l++;
    while (r >= 0 && a[r] > t)
      r--;
    L = max(L, r - t + 1);
    R = min(R, l + t - 1);
    if (r - l + 1 > t) {
      cout << "0\n";
      return;
    }
  }
  cout << max(R - L + 1, 0) << "\n";
}
int main(int _) {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> _; _--;)
    solve();
  return 0;
}