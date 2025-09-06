/*
 * Problem URL : https://codeforces.com/problemset/problem/2081/B
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, s, l, r, a[200005];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    s = l = 0;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i < n; i++)
      if (a[i] > a[i + 1]) {
        s++;
        r = i + 1;
        if (!l)
          l = i;
      }
    if (s % 2 || (s && a[r] - a[l] < r - l))
      cout << s / 2 + 1 << '\n';
    else
      cout << s / 2 << '\n';
  }
}