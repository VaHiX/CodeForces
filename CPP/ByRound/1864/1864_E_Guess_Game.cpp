/*
 * Problem URL : https://codeforces.com/problemset/problem/1864/E
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int T, n, a[200005];
int qpow(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1)
      res = 1ll * res * x % mod;
    x = 1ll * x * x % mod;
    y /= 2;
  }
  return res;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      int lst = 1, num = 0;
      for (int j = 29; j >= 0; j--) {
        if (!(a[i] & (1 << j)))
          continue;
        int l = lst, r = i - 1, pos = -1, lim = (a[i] >> j) << j;
        num++;
        while (l <= r) {
          int mid = (l + r) >> 1;
          if (a[mid] < lim)
            l = mid + 1, pos = mid;
          else
            r = mid - 1;
        }
        if (lst <= pos) {
          ans = (ans + 1ll * (pos - lst + 1) * (2 * num + 1) % mod) % mod;
          lst = pos + 1;
        }
      }
    }
    for (int l = 1, r = 1; l <= n; l = r + 1) {
      while (r < n && a[r + 1] == a[l])
        r++;
      ans = (ans + 1ll * (r - l + 1) * (r - l + 1) % mod *
                       (__builtin_popcount(a[l]) + 1) % mod) %
            mod;
    }
    cout << 1ll * ans * qpow(1ll * n * n % mod, mod - 2) % mod << '\n';
  }
  return 0;
}
