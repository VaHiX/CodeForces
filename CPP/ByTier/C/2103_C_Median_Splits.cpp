/*
 * Problem URL : https://codeforces.com/problemset/problem/2103/C
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
#define N 200005
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, k, i, a[N], l, r, s, fl, fr;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (i = 0; i < n; i++)
      cin >> a[i];
    for (i = 0; i < n; i++)
      if (a[i] > k)
        a[i] = 1;
      else
        a[i] = -1;
    s = 0;
    for (l = 0; l < n; l++) {
      s += a[l];
      if (s <= 0)
        break;
    }
    s = 0;
    for (r = n - 1; r >= 0; r--) {
      s += a[r];
      if (s <= 0)
        break;
    }
    if (r - l > 1)
      cout << "YES\n";
    else {
      s = fl = 0;
      for (l = 0; l < n - 1; l++) {
        s += a[l];
        if (s <= 0 && a[l] == -1)
          fl++;
      }
      s = fr = 0;
      for (r = n - 1; r > 0; r--) {
        s += a[r];
        if (s <= 0 && a[r] == -1)
          fr++;
      }
      if (fl >= 2 || fr >= 2)
        cout << "YES\n";
      else
        cout << "NO\n";
    }
  }
  return 0;
}
