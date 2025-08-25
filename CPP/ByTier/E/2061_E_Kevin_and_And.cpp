/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e5 + 1;

int t, n, m, k, C, a[kMaxN], b[2000], c[2000], mi[11], z[kMaxN * 10];
long long ans;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> t, b[0] = (1 << 30) - 1; t--;) {
    cin >> n >> m >> k, ans = C = 0;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
      cin >> b[1 << i];
    }
    for (int i = 1; i < (1 << m); i++) {
      c[i] = c[i ^ (i & (-i))] + 1, b[i] = b[i & (-i)] & b[i ^ (i & (-i))];
    }
    for (int i = 1; i <= n; i++) {
      fill(mi, mi + m + 1, 2e9);
      for (int j = 0; j < (1 << m); j++) {
        mi[c[j]] = min(mi[c[j]], (a[i] & b[j]));
      }
      ans += a[i];
      for (int j = 1; j <= m; j++) {
        z[++C] = mi[j - 1] - mi[j];
      }
    }
    sort(z + 1, z + C + 1);
    for (; k--; ans -= z[C--]) {
    }
    cout << ans << '\n';
  }
  return 0;
}