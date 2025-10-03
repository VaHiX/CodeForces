/*
 * Problem URL : https://codeforces.com/problemset/problem/2055/D
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
int n, k, l, a[200200], t, now, ti[200200];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> k >> l;
    k <<= 1;
    l <<= 1;
    t = 0;
    now = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      a[i] <<= 1;
    }
    t = a[1];
    now = k;
    for (int i = 2; i <= n; i++) {
      if (now <= a[i] + t && now >= a[i] - t) {
        now += k;
      } else if (now < a[i] - t) {
        int u = (a[i] - t - now) >> 1;
        t += u;
        now += u;
        now += k;
      } else {
        now = max(now, a[i] + t + k);
      }
    }
    cout << t + max(0, l - now) << "\n";
  }
  return 0;
}