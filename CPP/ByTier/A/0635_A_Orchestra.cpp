/*
 * Problem URL : https://codeforces.com/problemset/problem/635/A
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a[15][15];
int main() {
  int r, c, n, tt, x, y, ans = 0;
  cin >> r >> c >> n >> tt;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y;
    a[x][y] = 1;
  }
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= c; j++)
      for (int k = i; k <= r; k++)
        for (int l = j; l <= c; l++) {
          int cnt = 0;
          for (int p = i; p <= k; p++)
            for (int q = j; q <= l; q++)
              if (a[p][q])
                cnt++;
          if (cnt >= tt)
            ans++;
        }
  cout << ans;
  return 0;
}