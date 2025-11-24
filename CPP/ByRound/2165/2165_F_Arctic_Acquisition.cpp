// Problem: CF 2165 F - Arctic Acquisition
// https://codeforces.com/contest/2165/problem/F

/*
 * Problem: Arctic Acquisition
 * Algorithm: Segment Tree + Stack-based Preprocessing for 21435-subsequence detection
 * Time Complexity: O(n log n) per test case
 * Space Complexity: O(n) per test case
 *
 * The solution detects intervals that contain a 21435-subsequence by:
 * 1. Using stacks to precompute rightmost indices where elements are greater/smaller
 * 2. Using a segment tree to maintain and query maximum positions for subsequence detection
 * 3. Combining results to count all jagged intervals efficiently
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define For(i, a, b) for (int i = (a); i <= (b); ++i)
#define Rep(i, a, b) for (int i = (a); i >= (b); --i)
#define ll long long
#define SZ(x) ((int)((x).size()))
#define ALL(x) (x).begin(), (x).end()
using namespace std;
inline int read() {
  char c = getchar();
  int x = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar())
    f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    x = (x << 1) + (x << 3) + (c ^ 48);
  return f ? -x : x;
}
#define mod 998244353
struct modint {
  unsigned int x;
  modint(int o = 0) { x = o; }
  modint &operator=(int o) { return x = o, *this; }
  modint &operator+=(modint o) {
    return x = x + o.x >= mod ? x + o.x - mod : x + o.x, *this;
  }
  modint &operator-=(modint o) {
    return x = x < o.x ? x - o.x + mod : x - o.x, *this;
  }
  modint &operator*=(modint o) { return x = 1ll * x * o.x % mod, *this; }
  modint &operator^=(int b) {
    modint a = *this, c = 1;
    for (; b; b >>= 1, a *= a)
      if (b & 1)
        c *= a;
    return x = c.x, *this;
  }
  modint &operator/=(modint o) { return *this *= o ^= mod - 2; }
  friend modint operator+(modint a, modint b) { return a += b; }
  friend modint operator-(modint a, modint b) { return a -= b; }
  friend modint operator*(modint a, modint b) { return a *= b; }
  friend modint operator/(modint a, modint b) { return a /= b; }
  friend modint operator^(modint a, int b) { return a ^= b; }
  friend bool operator==(modint a, modint b) { return a.x == b.x; }
  friend bool operator!=(modint a, modint b) { return a.x != b.x; }
  bool operator!() { return !x; }
  modint operator-() { return x ? mod - x : 0; }
  bool operator<(const modint &b) const { return x < b.x; }
};
inline modint qpow(modint x, int y) { return x ^ y; }
vector<modint> fac, ifac, iv;
inline void initC(int n) {
  if (iv.empty())
    fac = ifac = iv = vector<modint>(2, 1);
  int m = iv.size();
  ++n;
  if (m >= n)
    return;
  iv.resize(n), fac.resize(n), ifac.resize(n);
  For(i, m, n - 1) {
    iv[i] = iv[mod % i] * (mod - mod / i);
    fac[i] = fac[i - 1] * i, ifac[i] = ifac[i - 1] * iv[i];
  }
}
inline modint C(int n, int m) {
  if (m < 0 || n < m)
    return 0;
  return initC(n), fac[n] * ifac[m] * ifac[n - m];
}
inline modint sign(int n) { return (n & 1) ? (mod - 1) : (1); }
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int, int> pii;
typedef vector<int> vi;
#define maxn 2000005
#define inf 0x3f3f3f3f
int n, a[maxn], tmp[maxn];
int st[maxn], tp;
int r1[maxn], r5[maxn], p4[maxn];
int tr[maxn << 2];
void upd(int p, int l, int r, int x, int y) {
  tr[p] = max(tr[p], y);
  if (l == r)
    return void();
  int mid = l + r >> 1;
  if (x <= mid)
    upd(p << 1, l, mid, x, y);
  else
    upd(p << 1 | 1, mid + 1, r, x, y);
}
int ask(int p, int l, int r, int ql, int qr) {
  if (ql > qr)
    return 0;
  if (l >= ql && r <= qr)
    return tr[p];
  int mid = l + r >> 1, res = 0;
  if (ql <= mid)
    res = max(res, ask(p << 1, l, mid, ql, qr));
  if (qr > mid)
    res = max(res, ask(p << 1 | 1, mid + 1, r, ql, qr));
  return res;
}
vi vec[maxn], vec1[maxn];
void work() {
  n = read();
  For(i, 0, n) vec[i].clear(), vec1[i].clear(), tmp[i] = 0;
  For(i, 1, n) a[i] = read();
  st[tp = 0] = n + 1;
  Rep(i, n, 1) {
    while (tp && a[i] > a[st[tp]])
      --tp;
    r5[i] = st[tp];
    st[++tp] = i;
  }
  st[tp = 0] = n + 1;
  Rep(i, n, 1) {
    while (tp && a[i] < a[st[tp]])
      --tp;
    r1[i] = st[tp];
    st[++tp] = i;
  }
  For(i, 0, n * 4) tr[i] = 0;
  For(i, 1, n) {
    p4[i] = 0;
    if (r5[i] != n + 1) {
      p4[i] = ask(1, 1, n, a[i], a[r5[i]]);
      if (p4[i])
        vec[p4[i]].pb(i);
    }
    upd(1, 1, n, a[i], i);
  }
  For(i, 1, n) {
    if (r1[i])
      vec1[r1[i]].pb(i);
  }
  For(i, 0, n * 4) tr[i] = 0;
  ll res = 0;
  For(i, 1, n) {
    for (int j : vec[i]) {
      int u = ask(1, 1, n, 1, a[j] - 1);
      tmp[r5[j]] = max(tmp[r5[j]], u);
    }
    for (int j : vec1[i]) {
      upd(1, 1, n, a[j], j);
    }
  }
  For(i, 1, n) tmp[i] = max(tmp[i], tmp[i - 1]), res += tmp[i];
  cout << res << "\n";
}
signed main() {
  int T = read();
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/