// Problem: CF 2161 E - Left is Always Right
// https://codeforces.com/contest/2161/problem/E

/*
Algorithm: Dynamic Programming with Sliding Window and Modular Arithmetic
Time Complexity: O(N * K) where N is the length of the string and K is the substring length
Space Complexity: O(N + K) for storing precomputed factorials and auxiliary data structures

The solution uses a sliding window approach to count valid assignments of '?' characters
such that every substring of length K satisfies the "left is always right" condition.
It processes the string in two passes (original and flipped) to cover all cases,
and uses combinatorics (ncr) to count valid combinations of 0s and 1s in the sliding window.

The key insight is that for a substring to be good, the first character must appear more than
the other characters in that substring. Since K is odd, the first character needs to appear at least (K+1)/2 times.
*/
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
template <typename T> T mod_inv_in_range(T a, T m) {
  T x = a, y = m;
  T vx = 1, vy = 0;
  while (x) {
    T k = y / x;
    y %= x;
    vy -= k * vx;
    std::swap(x, y);
    std::swap(vx, vy);
  }
  assert(y == 1);
  return vy < 0 ? m + vy : vy;
}
template <typename T> struct extended_gcd_result {
  T gcd;
  T coeff_a, coeff_b;
};
template <typename T> extended_gcd_result<T> extended_gcd(T a, T b) {
  T x = a, y = b;
  T ax = 1, ay = 0;
  T bx = 0, by = 1;
  while (x) {
    T k = y / x;
    y %= x;
    ay -= k * ax;
    by -= k * bx;
    std::swap(x, y);
    std::swap(ax, ay);
    std::swap(bx, by);
  }
  return {y, ay, by};
}
template <typename T> T mod_inv(T a, T m) {
  a %= m;
  a = a < 0 ? a + m : a;
  return mod_inv_in_range(a, m);
}
template <int MOD_> struct modnum {
  static constexpr int MOD = MOD_;
  static_assert(MOD_ > 0, "MOD must be positive");

private:
  int v;

public:
  modnum() : v(0) {}
  modnum(int64_t v_) : v(int(v_ % MOD)) {
    if (v < 0)
      v += MOD;
  }
  explicit operator int() const { return v; }
  friend std::ostream &operator<<(std::ostream &out, const modnum &n) {
    return out << int(n);
  }
  friend std::istream &operator>>(std::istream &in, modnum &n) {
    int64_t v_;
    in >> v_;
    n = modnum(v_);
    return in;
  }
  friend bool operator==(const modnum &a, const modnum &b) {
    return a.v == b.v;
  }
  friend bool operator!=(const modnum &a, const modnum &b) {
    return a.v != b.v;
  }
  modnum inv() const {
    modnum res;
    res.v = mod_inv_in_range(v, MOD);
    return res;
  }
  friend modnum inv(const modnum &m) { return m.inv(); }
  modnum neg() const {
    modnum res;
    res.v = v ? MOD - v : 0;
    return res;
  }
  friend modnum neg(const modnum &m) { return m.neg(); }
  modnum operator-() const { return neg(); }
  modnum operator+() const { return modnum(*this); }
  modnum &operator++() {
    v++;
    if (v == MOD)
      v = 0;
    return *this;
  }
  modnum &operator--() {
    if (v == 0)
      v = MOD;
    v--;
    return *this;
  }
  modnum &operator+=(const modnum &o) {
    v -= MOD - o.v;
    v = (v < 0) ? v + MOD : v;
    return *this;
  }
  modnum &operator-=(const modnum &o) {
    v -= o.v;
    v = (v < 0) ? v + MOD : v;
    return *this;
  }
  modnum &operator*=(const modnum &o) {
    v = int(int64_t(v) * int64_t(o.v) % MOD);
    return *this;
  }
  modnum &operator/=(const modnum &o) { return *this *= o.inv(); }
  friend modnum operator++(modnum &a, int) {
    modnum r = a;
    ++a;
    return r;
  }
  friend modnum operator--(modnum &a, int) {
    modnum r = a;
    --a;
    return r;
  }
  friend modnum operator+(const modnum &a, const modnum &b) {
    return modnum(a) += b;
  }
  friend modnum operator-(const modnum &a, const modnum &b) {
    return modnum(a) -= b;
  }
  friend modnum operator*(const modnum &a, const modnum &b) {
    return modnum(a) *= b;
  }
  friend modnum operator/(const modnum &a, const modnum &b) {
    return modnum(a) /= b;
  }
};
template <typename T> T pow(T a, long long b) {
  assert(b >= 0);
  T r = 1;
  while (b) {
    if (b & 1)
      r *= a;
    b >>= 1;
    a *= a;
  }
  return r;
}
using num = modnum<998244353>;
vector<num> fact, ifact;
void init() {
  // Precompute factorials for combinations
  fact.resize(200005);
  ifact.resize(200005);
  fact[0] = 1;
  for (int i = 1; i < 200005; i++) {
    fact[i] = fact[i - 1] * i;
  }
  ifact[200004] = fact[200004].inv();
  for (int i = 200003; i >= 0; i--) {
    ifact[i] = ifact[i + 1] * (i + 1);
  }
}
num ncr(int n, int r) {
  if (r > n || r < 0) return 0;
  return fact[n] * ifact[r] * ifact[n - r];
}
void solve() {
  int N, K;
  cin >> N >> K;
  string S;
  cin >> S;
  num ans = 0;
  int L = K - 1;
  for (int it = 0; it < 2; it++) {
    int pref1s = 0;
    for (int i = 0; i < N - L; i++)
      if (S[i] == '1')
        pref1s++;
    if (pref1s == 0) {
      int c0 = 0;
      int c1 = 0;
      for (int i = N - L; i < N; i++) {
        if (S[i] == '0')
          c0++;
        if (S[i] == '1')
          c1++;
      }
      for (int X = L / 2; X <= L; X++) {
        if (c0 <= X && c1 <= L - X) {
          ans += ncr(L - c0 - c1, X - c0);
        }
      }
    }
    vector<int> nmask(4);
    vector<int> mask(L, 0);
    nmask[0] += L;
    auto upd = [&](int a, int v) {
      nmask[mask[a]]--;
      mask[a] = v;
      nmask[mask[a]]++;
    };
    for (int i = N - L; i < N; i++) {
      if (S[i] == '0')
        upd(i % L, 1);
      if (S[i] == '1')
        upd(i % L, 2);
    }
    for (int x = N - L; x >= 1; x--) {
      if (x < N - L && pref1s == 0) {
        int saved = -1;
        saved = mask[x % L];
        upd(x % L, mask[x % L] | 2);
        if (nmask[3] == 0) {
          int a = nmask[1];
          int b = nmask[2];
          if (a <= L / 2 && b <= L / 2) {
            ans += ncr(L / 2 - a + L / 2 - b, L / 2 - a);
          }
        }
        upd(x % L, saved);
      }
      if (S[x - 1] == '1') {
        pref1s--;
        upd((x - 1) % L, mask[(x - 1) % L] | 2);
      } else if (S[x - 1] == '0') {
        upd((x - 1) % L, mask[(x - 1) % L] | 1);
      }
    }
    for (char &x : S) {
      if (x == '0')
        x = '1';
      else if (x == '1')
        x = '0';
    }
  }
  cout << ans << '\n';
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  init();
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/