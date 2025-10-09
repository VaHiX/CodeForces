/*
 * Problem URL : https://codeforces.com/problemset/problem/2096/H
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define inf 1000000000
#define infll 1000000000000000000ll
#define pii pair<int, int>
#define rep(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define per(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define F(i, a, b) for (int i = a, i##end = b; i <= i##end; i++)
#define dF(i, a, b) for (int i = a, i##end = b; i >= i##end; i--)
#define cmh(sjy) while (sjy--)
#define lowbit(x) ((x) & (-(x)))
#define HH printf("\n")
#define eb emplace_back
#define poly vector<int>
#define SZ(x) ((int)x.size())
using namespace std;
void fre() {
  // freopen("xor.in","r",stdin),freopen("xor.out","w",stdout);
}
template <typename T> inline void chkmax(T &x, const T &y) {
  x = std::max(x, y);
}
template <typename T> inline void chkmin(T &x, const T &y) {
  x = std::min(x, y);
}
const int mod = 998244353, maxn = 300005;
inline int qpow(int x, ll y) {
  int res = 1;
  for (; y; y >>= 1, x = 1ll * x * x % mod)
    if (y & 1)
      res = 1ll * res * x % mod;
  return res;
}
inline void inc(int &x, const int y) {
  x = (x + y >= mod) ? (x + y - mod) : (x + y);
}
inline void dec(int &x, const int y) { x = (x >= y) ? (x - y) : (x + mod - y); }
inline void mul(int &x, const int y) { x = 1ll * x * y % mod; }
inline int add(const int x, const int y) {
  return (x + y >= mod) ? (x + y - mod) : (x + y);
}
inline int sub(const int x, const int y) {
  return (x >= y) ? (x - y) : (x + mod - y);
}
int n, m, lef[maxn], rig[maxn], ans[maxn];
pii a[maxn];
void solve() {
  cin >> m >> n;
  const int mx = (1 << n) - 1;
  F(i, 1, m) cin >> lef[i] >> rig[i];
  F(s, 0, mx) ans[s] = 0;
  F(t, 0, n - 1) {
    int A = (1 << (n - 1 - t)) - 1, B = (1 << t) - 1, x, y, p, q;
    F(s, 0, A) a[s] = mkp(1, 1);
    F(i, 1, m) {
      int l = lef[i], r = rig[i];
      if ((l >> t) & 1)
        x = (1 << t) - (B & l);
      else
        x = (B & l);
      if ((r >> t) & 1)
        y = (1 << t) - ((B & r) + 1);
      else
        y = ((B & r) + 1);
      p = (l >> (t + 1)), q = (r >> (t + 1));
      mul(a[p ^ q].fi, sub(y, x)), mul(a[p ^ q].se, add(x, y)),
          mul(a[q].se, mod - 1);
    }
    F(i, 0, n - t - 2) F(s, 0, A) if (!((s >> i) & 1)) {
      pii &x = a[s], &y = a[s ^ (1 << i)];
      p = 1ll * x.fi * y.se % mod, q = 1ll * x.se * y.fi % mod;
      mul(x.fi, y.fi), mul(x.se, y.se), y = mkp(p, q);
    }
    F(s, 0, A) ans[(s << 1 | 1) << t] = a[s].fi;
  }
  ans[0] = 1;
  F(i, 1, m) mul(ans[0], rig[i] - lef[i] + 1);
  F(i, 0, n - 1) F(s, 0, mx) if (!((s >> i) & 1)) {
    int &x = ans[s], &y = ans[s ^ (1 << i)];
    const int t = sub(x, y);
    inc(x, y), y = t;
  }
  const int I = qpow(1 << n, mod - 2);
  F(s, 0, mx) mul(ans[s], I);
  int res = 0, pw = 1;
  F(s, 0, mx) res ^= ((1ll * ans[s] * pw) % mod), pw = add(pw, pw);
  cout << res << '\n';
}
signed main() {
  fre(), ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int zsy = 1;
  cin >> zsy;
  F(____, 1, zsy) solve();
}
// g++ cf2096h.cpp -o a -std=c++14 -O2