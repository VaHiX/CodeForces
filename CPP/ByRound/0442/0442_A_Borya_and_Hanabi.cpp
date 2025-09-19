/*
 * Problem URL : https://codeforces.com/contest/442/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

const string col = "RGBYW";
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int A[n], B[n];
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < 5; ++j) {
      if (s[0] == col[j]) {
        A[i] = j;
        break;
      }
    }

    B[i] = s[1] - '1';
  }

  int ans = 10;
  for (int a = 0; a < (1 << 5); ++a)
    for (int b = 0; b < (1 << 5); ++b) {
      bool ok = true;
      for (int i = 0; i < n; ++i)
        if (ok)
          for (int j = 0; j < i; ++j)
            if (ok) {
              if (A[i] != A[j] || B[i] != B[j]) {
                int ii = (a & (1 << A[i]) ? 64 << A[i] : 0) |
                         (b & (1 << B[i]) ? 1 << B[i] : 0);
                int jj = (a & (1 << A[j]) ? 64 << A[j] : 0) |
                         (b & (1 << B[j]) ? 1 << B[j] : 0);

                if (ii == jj)
                  ok = false;
              }
            }
      if (ok)
        ans = min(ans, __builtin_popcount(a) + __builtin_popcount(b));
    }
  cout << ans << endl;
  return 0;
}