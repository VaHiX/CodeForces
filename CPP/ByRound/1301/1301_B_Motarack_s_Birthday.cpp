/*
 * Problem URL : https://codeforces.com/problemset/problem/1301/B
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, i, j, k, a[200001], mx = -2e9, mn = 2e9;
    cin >> n;
    for (i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    a[n] = 100;
    for (i = 0; i < n; i++) {
      if ((i > 0 && a[i - 1] == -1 || a[i + 1] == -1) && a[i] != -1) {
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
      }
    }
    int u = (mx + mn) / 2, dif = -2e9;
    for (i = 1; i < n; i++) {
      if (a[i - 1] == -1)
        a[i - 1] = u;
      if (a[i] == -1)
        a[i] = u;
      dif = max(dif, abs(a[i] - a[i - 1]));
    }
    cout << dif << ' ' << u << endl;
  }
}
