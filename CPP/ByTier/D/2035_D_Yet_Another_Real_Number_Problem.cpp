/*
 * Problem URL : https://codeforces.com/contest/2035/problem/D
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 2e5 + 3, Mod = 1e9 + 7;

int T, n, top, a[MAXN], c[MAXN], stk[MAXN];
ll b[MAXN];

void Solve() {
  cin >> n, top = 0;
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], b[i] = 1;
    ll t = 1;
    c[i] = 0;
    for (; top && a[stk[top]] <= a[i] * (1ll << min(c[i], 30)); top--) {
      (b[i] *= b[stk[top]]) %= Mod, c[i] += c[stk[top]];
      (ans -= a[stk[top]] * (b[stk[top]] - 1)) %= Mod;
    }
    (ans += a[i] * b[i] + Mod) %= Mod, stk[++top] = i;
    for (; a[i] % 2 == 0; a[i] >>= 1, b[i] <<= 1, c[i]++)
      ;
    b[i] %= Mod, cout << ans << " \n"[i == n];
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T--;) {
    Solve();
  }
  return 0;
}
