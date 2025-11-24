// Problem: CF 717 A - Festival Organization
// https://codeforces.com/contest/717/problem/A

/*
 * Problem: Festival Organization
 * 
 * Purpose: Count the number of ways to select k different tours of the same length
 *          between l and r, where each tour is a binary string (1 = concert, 0 = day-off),
 *          and no two consecutive days-off are allowed.
 *
 * Algorithm: The solution uses generating functions and dynamic programming.
 *            It computes the number of valid sequences of a given length using:
 *            - Generating function for sequences without two consecutive zeros
 *            - Polynomial coefficients for inclusion-exclusion
 *            - Matrix exponentiation for fast computation
 *            - Inclusion-exclusion principle via Möbius inversion or direct calculation
 *
 * Time Complexity: O(k^2 * log(r)) due to polynomial computations and fast exponentiation
 * Space Complexity: O(k^2) for storing coefficients, factorials, and choose table
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
static const ll PRIME = 1e9 + 7;
static const ll K = 200 + 10;
ll k, l, r;
vector<ll> coefs(K);
vector<ll> fac(K);
vector<ll> facInv(K);
vector<vector<ll>> choose(K, vector<ll>(K));
inline ll Mod(ll n) { return (n % PRIME + PRIME) % PRIME; }
inline ll Mul(ll a, ll b) { return (a * b) % PRIME; }
inline ll Inv(ll n) {
  ll a = n, b = PRIME, u = 1, v = 0;
  while (b) {
    ll t = a / b;
    swap(a -= b * t, b);
    swap(u -= v * t, v);
  }
  return Mod(u);
}
struct Num {
  ll a, b;
  inline Num() : a(0), b(0) {}
  explicit inline Num(ll av) : a(Mod(av)), b(0) {}
  inline Num(ll av, ll bv) : a(Mod(av)), b(Mod(bv)) {}
  inline Num(ll av, ll bv, ll cv) {
    Num result = Num(av, bv) / Num(cv);
    *this = result;
  }
  friend inline Num operator+(const Num &x, const Num &y) {
    return Num(x.a + y.a, x.b + y.b);
  }
  friend inline Num operator*(const Num &x, const Num &y) {
    return Num(x.a * y.a + 5 * x.b * y.b, x.a * y.b + x.b * y.a);
  }
  friend inline Num operator-(const Num &x, const Num &y) {
    return Num(x.a - y.a, x.b - y.b);
  }
  friend inline Num operator/(const Num &x, const Num &y) {
    ll a = x.a * y.a - 5 * x.b * y.b;
    ll b = -x.a * y.b + x.b * y.a;
    ll c = y.a * y.a - 5 * y.b * y.b;
    a = Mod(a);
    b = Mod(b);
    c = Mod(c);
    ll ci = Inv(c);
    return Num(a * ci, b * ci);
  }
  Num inline operator-() const { return Num(-a, -b); }
  bool inline operator==(const Num &o) const { return (a == o.a && b == o.b); }
  inline Num Inverse() const { return Num(1) / *this; }
  inline Num Pow(ll pow) const {
    Num x(a, b);
    Num result(1);
    while (pow) {
      if (pow & 1) {
        result = result * x;
      }
      pow >>= 1;
      x = x * x;
    }
    return result;
  }
};
inline void FillKLR() { cin >> k >> l >> r; }
inline void FillPolyCoefficients() {
  vector<ll> temp(K);
  coefs[0] = 1;
  for (ll i = 0; i < k; i++) {
    temp[0] = Mod(-i * coefs[0]);
    for (ll j = 1; j <= i + 1; j++) {
      temp[j] = Mod(coefs[j - 1] - i * coefs[j]);
    }
    temp.swap(coefs);
  }
}
inline void FillFacInvChoose() {
  fac[0] = 1;
  for (ll i = 1; i <= k; i++) {
    fac[i] = Mul(fac[i - 1], i);
  }
  facInv[k] = Inv(fac[k]);
  for (ll i = k - 1; i >= 0; i--) {
    facInv[i] = Mul(facInv[i + 1], i + 1);
  }
  for (ll i = 0; i <= k; i++) {
    for (ll j = 0; j <= i; j++) {
      choose[i][j] = Mul(fac[i], Mul(facInv[j], facInv[i - j]));
    }
  }
}
inline Num GetH(ll n, ll m) {
  static const Num A = Num(1, 1, 2);
  static const Num B = Num(1, -1, 2);
  static const Num root5Inv = Num(0, 1).Inverse();
  static const Num ABinc = A * B.Inverse();
  const Num ABNinc = ABinc.Pow(n + 1);
  Num AB = B.Pow(m);
  Num ABN = AB.Pow(n + 1);
  Num num, den, term;
  Num sum(0);
  for (ll j = 0; j <= m; j++) {
    if (AB == Num(1)) {
      term = Num(n + 1);
    } else {
      den = AB - Num(1);
      num = ABN - Num(1);
      term = (num / den);
    }
    term = term * Num(choose[m][j]);
    sum = ((m - j) & 1) ? sum - term : sum + term;
    AB = AB * ABinc;
    ABN = ABN * ABNinc;
  }
  return root5Inv.Pow(m) * sum;
}
inline Num GetQ(ll n) {
  Num sum(0);
  for (ll j = 0; j <= k; j++) {
    sum = sum + Num(coefs[j]) * GetH(n, j);
  }
  return Num(facInv[k]) * sum;
}
int main(int argc, char const *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  FillKLR();
  FillPolyCoefficients();
  FillFacInvChoose();
  Num answer = GetQ(r + 2) - GetQ(l + 1);
  cout << answer.a << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/