// Problem: CF 1992 G - Ultra-Meow
// https://codeforces.com/contest/1992/problem/G

/*
Code Purpose:
This program calculates the "MEOW" value of an array of integers from 1 to n.
MEOW(a) is defined as the sum of MEX(b, |b|+1) over all distinct subsets b of array a.
MEX(S,k) is the k-th smallest positive integer not present in set S.

Algorithms/Techniques:
- Mathematical combinatorics and modular arithmetic
- Dynamic programming with precomputed factorials and inverse factorials
- Efficient computation of binomial coefficients

Time Complexity: O(n^2) per test case due to precomputation of factorials and binomial coefficients.
Space Complexity: O(n) for storing factorials and inverse factorials, plus additional space for intermediate calculations.

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
struct modp {
  ll MOD;
  vector<ll> F = {1}, IF = {1}, C;
  modp(ll MOD) { this->MOD = MOD; }
  ll fix(ll a) {
    if (a < 0)
      return fix(a + MOD);
    return a % MOD;
  }
  ll add(ll a) { return a; }
  template <typename... Rest> ll add(ll x, Rest... rest) {
    return (x + add(rest...)) % MOD;
  }
  ll addto(ll &a, ll b) { return a = add(a, b); }
  template <typename... Rest> ll sub(ll x, Rest... rest) {
    return (x - add(rest...) + MOD) % MOD;
  }
  ll subto(ll &a, ll b) { return a = sub(a, b); }
  ll mul(ll a) { return a; }
  template <typename... Rest> ll mul(ll x, Rest... rest) {
    return x * mul(rest...) % MOD;
  }
  ll multo(ll &a, ll b) { return a = mul(a, b); }
  ll sqr(ll a) { return a * a % MOD; }
  ll pow(ll a, ll b) {
    return b == 0   ? 1
           : b == 1 ? a
           : b % 2  ? mul(pow(a, b - 1ll), a)
                    : sqr(pow(a, b / 2ll));
  }
  ll inv(ll a) { return pow(a, MOD - 2ll); }
  ll div(ll a, ll b) { return a * inv(b) % MOD; }
  ll tri(ll a) { return div(mul(a, a + 1), 2); }
  void CF(int lim) {
    F.resize(lim);
    for (int i = 1; i < lim; i++)
      F[i] = mul(F[i - 1], i);
  }
  void CIF() {
    IF.resize(F.size());
    transform(F.begin(), F.end(), IF.begin(),
              [&](ll x) -> ll { return this->inv(x); });
  }
  void CC() {
    C.resize(F.size() / 2);
    for (int i = 0; i < F.size() / 2; i++)
      C[i] = div(nCk(i * 2, i), i + 1);
  }
  ll fact(ll a) {
    if (0 <= a && a < F.size())
      return F[a];
    return a >= 0 ? mul(fact(a - 1ll), a) : 0;
  }
  ll invfact(ll a) {
    if (0 <= a && a < IF.size())
      return IF[a];
    return inv(fact(a));
  }
  ll nCk(ll n, ll k) {
    return n >= k ? mul(fact(n), mul(invfact(k), invfact(n - k))) : 0;
  }
  ll nPk(ll n, ll k) { return n >= k ? mul(fact(n), invfact(n - k)) : 0; }
};
modp M(1'000'000'007LL);
int main() {
  cin.tie(0)->sync_with_stdio(0);
  M.CF(5005);
  M.CIF();
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    // Compute first part: (2^(n-1)) * (n + 2)
    ll first = M.mul(M.pow(2, n - 1), n + 2);
    ll second = 0;
    // Compute second sum: sum_{S=1}^{n/2} (S + 1) * C(n, S - 1)
    for (int S = 1; S <= n / 2; S++)
      M.addto(second, M.mul(S + 1, M.nCk(n, S - 1)));
    ll third =
        n % 2
            ? M.add(M.div(M.mul(n, M.sub(M.pow(4, n / 2), M.nCk(n - 1, n / 2))),
                          2),
                    M.mul(n / 2 + 1, M.nCk(n, n / 2 + 1)))
            : M.mul(M.pow(2, n - 2), n);
    // Final answer is the sum of first, second, and third parts
    cout << M.add(first, second, third) << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/