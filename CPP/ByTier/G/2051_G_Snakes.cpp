/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int kMaxN = 21;

int n, q, a[kMaxN][kMaxN], mi[kMaxN][kMaxN], c[kMaxN],
    dp[1 << (kMaxN - 1)][kMaxN], z[1 << (kMaxN - 1)], ans = 2e9;
char y;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q;
  for (int i = 1, x; i <= q; i++) {
    cin >> x >> y;
    if (y == '+') {
      c[x]++;
      for (int j = 1; j <= n; j++) {
        a[x][j]--, mi[x][j] = min(mi[x][j], a[x][j]);
      }
    } else {
      for (int j = 1; j <= n; j++) {
        a[j][x]++;
      }
    }
  }
  fill(dp[0], dp[(1 << n) - 1] + n + 1, 2e9);
  for (int i = 1; i <= n; i++) {
    dp[1 << (i - 1)][i] = 1, z[1 << (i - 1)] = i;
  }
  for (int i = 1; i < (1 << n); i++) {
    for (int j = i; j; j ^= (j & (-j))) {
      for (int k = (1 << n) - 1 - i; k; k ^= (k & (-k))) {
        dp[i ^ (k & (-k))][z[k & (-k)]] =
            min(dp[i ^ (k & (-k))][z[k & (-k)]],
                dp[i][z[j & (-j)]] + 1 - mi[z[j & (-j)]][z[k & (-k)]]);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[(1 << n) - 1][i] + c[i]);
  }
  cout << ans;
  return 0;
}