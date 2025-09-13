/*
 * Problem URL : https://codeforces.com/contest/2137/problem/F
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
int a[200000], b[200000], l[200000];
int stk[200000], p;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int T, n, i, L, R, mid;
  long long ans;
  for (cin >> T; T > 0; T--) {
    cin >> n;
    for (i = 0; i < n; i++)
      cin >> a[i];
    for (i = 0; i < n; i++)
      cin >> b[i];
    p = 0;
    for (i = 0; i < n; i++) {
      while (p > 0 && a[stk[p - 1]] < a[i])
        p--;
      if (a[i] == b[i])
        l[i] = i;
      else {
        L = -1;
        R = p;
        while (R - L > 1) {
          mid = (L + R) / 2;
          if (a[stk[mid]] >= max(a[i], b[i]))
            L = mid;
          else
            R = mid;
        }
        if (L == -1)
          l[i] = -1;
        else
          l[i] = stk[L];
      }
      stk[p] = i;
      p++;
    }
    ans = 0;
    for (i = 0; i < n; i++)
      ans += (long long)(l[i] + 1) * (long long)(n - i);
    cout << ans << '\n';
  }
  return 0;
}