/*
 * Problem URL : https://codeforces.com/problemset/problem/2078/G
 * Submit Date : 2025-08-22
 */

#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i++)
#define Rof(i, a, b) for (int i = (a); i >= (b); i--)
using namespace std;
const int N = 2e5 + 5, mod = 998244353;
int n, a[N], b[N];
int top, ans, st[N], L[N], R[N];
inline void add(int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}
inline void sub(int &x, int y) {
  x += mod - y;
  if (x >= mod)
    x -= mod;
}
void Solve() {
  cin >> n;
  For(i, 1, n) cin >> a[i];
  For(i, 1, n) {
    if (i & 1)
      b[i] = b[i - 1] + a[i];
    else
      b[i] = b[i - 1] - a[i];
  }
  top = ans = 0;
  For(i, 1, n) R[i] = n;
  For(i, 1, n) {
    while (top && b[st[top]] < b[i])
      R[st[top]] = i - 1, top--;
    L[i] = !top ? 0 : st[top] + 1;
    st[++top] = i;
  }
  For(i, 1, n)(ans += (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) %
                      mod) %= mod;
  top = 0;
  For(i, 1, n) R[i] = n;
  For(i, 0, n) {
    while (top && b[st[top]] >= b[i])
      R[st[top]] = i - 1, top--;
    L[i] = !top ? 0 : st[top] + 1;
    st[++top] = i;
  }
  For(i, 1, n)(ans -= (R[i] - i + 1) * (i - L[i] + 1) % mod * (b[i] % mod) %
                      mod) %= mod;
  ans = (ans % mod + mod) % mod;
  cout << ans << '\n';
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int T = 1;
  cin >> T;
  while (T--)
    Solve();
  return 0;
}