/*
 * Problem URL : https://codeforces.com/problemset/problem/2053/G
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
template <int P> class mod_int {
  using Z = mod_int;

private:
  static int mo(int x) { return x < 0 ? x + P : x; }

public:
  int x;
  int val() const { return x; }
  mod_int() : x(0) {}
  template <class T>
  mod_int(const T &x_)
      : x(x_ >= 0 && x_ < P ? static_cast<int>(x_)
                            : mo(static_cast<int>(x_ % P))) {}
  bool operator==(const Z &rhs) const { return x == rhs.x; }
  bool operator!=(const Z &rhs) const { return x != rhs.x; }
  Z operator-() const { return Z(x ? P - x : 0); }
  Z pow(long long k) const {
    Z res = 1, t = *this;
    while (k) {
      if (k & 1)
        res *= t;
      if (k >>= 1)
        t *= t;
    }
    return res;
  }
  Z &operator++() {
    x < P - 1 ? ++x : x = 0;
    return *this;
  }
  Z &operator--() {
    x ? --x : x = P - 1;
    return *this;
  }
  Z operator++(int) {
    Z ret = x;
    x < P - 1 ? ++x : x = 0;
    return ret;
  }
  Z operator--(int) {
    Z ret = x;
    x ? --x : x = P - 1;
    return ret;
  }
  Z inv() const { return pow(P - 2); }
  Z &operator+=(const Z &rhs) {
    (x += rhs.x) >= P && (x -= P);
    return *this;
  }
  Z &operator-=(const Z &rhs) {
    (x -= rhs.x) < 0 && (x += P);
    return *this;
  }
  Z operator-() { return -x; }
  Z &operator*=(const Z &rhs) {
    x = 1ULL * x * rhs.x % P;
    return *this;
  }
  Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                                             \
  friend T operator o(const Z &lhs, const Z &rhs) {                            \
    Z res = lhs;                                                               \
    return res o## = rhs;                                                      \
  }
  setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
      friend istream &
      operator>>(istream &is, mod_int &x) {
    long long tmp;
    is >> tmp;
    x = tmp;
    return is;
  }
  friend ostream &operator<<(ostream &os, const mod_int &x) {
    os << x.val();
    return os;
  }
};
typedef long long ll;
typedef unsigned long long ull;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
constexpr int p = 993244853;
using Hash = mod_int<p>;
// using Hash = ull;
const Hash base = rnd() % 20091119 + 30;
string s, t;
Hash st;
int mnlen;
Hash S[5000020];
Hash T[5000020];
Hash pw[5000020];
// int doit;
inline Hash SUM(const int l, const int r, const Hash *s) {
  return s[r] - s[l - 1] * pw[r - l + 1];
}
int n, m;
inline bool check(const int l, const int r, const Hash x, const int len,
                  const Hash *S) {
  // doit++;
  return r - l + 1 >= len && SUM(l, l + len - 1, S) == x &&
         SUM(l, r - len, S) == SUM(l + len, r, S);
}
inline bool calc(const int L1, const int R1, const int L2, const int R2,
                 const int l1, const int l2) {
  if (mnlen && check(L1, R1, st, mnlen, S) && check(L2, R2, st, mnlen, S)) {
    if (check(1, m, st, mnlen, T)) {
      for (int i = 0; i <= m; i += l2) {
        if (!((m - i) % l1))
          return 1;
      }
      return 0;
    }
  }
  const Hash s1 = SUM(L1, R1, S);
  const Hash s2 = SUM(L2, R2, S);
  int l = 1, r = l2 / l1, okcnt = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    if (check(L2, L2 + mid * l1 - 1, s1, l1, S))
      l = (okcnt = mid) + 1;
    else
      r = mid - 1;
  }
  const int tt = (n / l1);
  int ed = 0;
  while (ed <= m) {
    int L = 1, R = (m - ed) / l1, cnt = 0;
    int tcnt = 0;
    while (tcnt + tt <= R && check(ed + 1, ed + (tcnt + tt) * l1, s1, l1, T))
      tcnt += tt;
    L = max(L, tcnt);
    R = min(R, tcnt + tt - 1);
    // cerr << ed << ' ' << L << ' ' << R << '\n';
    while (L <= R) {
      int mid = L + R >> 1;
      if (check(ed + 1, ed + mid * l1, s1, l1, T))
        L = (cnt = mid) + 1;
      else
        R = mid - 1;
    }
    if (ed + cnt * l1 + 1 > m)
      return 1;
    // int st = ed + (cnt - okcnt) * l1 + 1;
    // if (st > ed && st + l2 - 1 <= m && SUM(st, st + l2 - 1, T) == s2)
    // {
    //     ed = st + l2 - 1;
    //     continue;
    // }
    // return 0;
    bool found = 0;
    for (int st = ed + (cnt - okcnt) * l1 + 1, cnt = 1; cnt <= 2 && st > ed;
         st -= l1, cnt++) {
      if (st + l2 - 1 <= m && SUM(st, st + l2 - 1, T) == s2) {
        ed = st + l2 - 1;
        found = 1;
        break;
      }
    }
    if (!found)
      return 0;
  }
  return 1;
}
void solve() {
  // build();
  mnlen = 0;
  cin >> n >> m >> s >> t;
  s = ' ' + s;
  t = ' ' + t;
  for (int i = 1; i <= n; i++)
    S[i] = S[i - 1] * base + Hash(s[i] - 'a' + 1);
  for (int i = 1; i <= m; i++)
    T[i] = T[i - 1] * base + Hash(t[i] - 'a' + 1);
  for (int i = 1; i <= n; i++) {
    if (n % i == 0 && check(1, n, S[i], i, S)) {
      st = S[i];
      mnlen = i;
      break;
    }
  }
  for (int i = 1; i < n; i++)
    putchar('0' ^ (i <= n - i ? calc(1, i, i + 1, n, i, n - i)
                              : calc(i + 1, n, 1, i, n - i, i)));
  putchar('\n');
  // cerr << doit << '\n';
}
int main() {
  // freopen("out.txt", "r", stdin);
  pw[0] = Hash(1);
  for (int i = 1; i <= 5'000'000; i++)
    pw[i] = pw[i - 1] * base;
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  // cerr << fixed << setprecision(10) << 1.0 * clock() / CLOCKS_PER_SEC <<
  // '\n';
  return 0;
}