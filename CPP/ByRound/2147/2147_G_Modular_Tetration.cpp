// Problem: CF 2147 G - Modular Tetration
// https://codeforces.com/contest/2147/problem/G

// Problem: G. Modular Tetration
//
// Purpose:
// This program calculates the density of m-tetrative integers for a given m = x * y * z.
// An integer a is m-tetrative if the sequence b_n = a^(b_{n-1}) with b_0 = 1 stabilizes to 1 modulo m.
//
// Algorithms:
// - Sieve of smallest prime factor (SPF) for factorization
// - Modular exponentiation with precomputed modular inverses
// - Use of Euler's totient function and Carmichael function concepts
// - Mathematical analysis involving multiplicative functions and modular arithmetic
//
// Time Complexity: O(LIM * log(log(LIM)) + T * sqrt(LIM) * log(LIM))
// Space Complexity: O(LIM)
#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
const int LIM = 1'000'000;
const int MOD = 998244353;
long long modpow(long long a, long long e) {
  long long r = 1 % MOD;
  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }
  return r;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<int> spf(LIM + 1); // smallest prime factor
  iota(spf.begin(), spf.end(), 0); // initialize to identity
  for (int i = 2; i * 1LL * i <= LIM; ++i)
    if (spf[i] == i) {
      for (int j = i * i; j <= LIM; j += i)
        if (spf[j] == j)
          spf[j] = i;
    }
  auto factorize = [&](long long n) { // factorize number into prime powers
    vector<pair<int, int>> fac;
    while (n > 1) {
      int p = (n <= LIM ? spf[n] : 0); // get smallest prime factor
      if (p == 0) {
        fac.push_back({(int)n, 1});
        break;
      }
      int c = 0;
      while (n % p == 0) {
        n /= p;
        ++c;
      }
      fac.push_back({p, c});
    }
    return fac;
  };
  vector<int> inv(LIM + 1); // precompute modular inverses
  inv[1] = 1;
  for (int i = 2; i <= LIM; ++i)
    inv[i] = int(1LL * (MOD - MOD / i) * inv[MOD % i] % MOD);
  auto pow_inv = [&](int a, long long e) { return modpow(inv[a], e); }; // modular inverse power
  int T;
  if (!(cin >> T))
    return 0;
  while (T--) {
    long long x, y, z;
    cin >> x >> y >> z;
    unordered_map<int, long long> pe; // prime exponents map
    pe.reserve(32);
    auto add_fac = [&](long long n) { // accumulate prime power exponents from n
      for (auto [p, c] : factorize(n))
        pe[p] += c;
    };
    add_fac(x);
    add_fac(y);
    add_fac(z);
    long long ans = 1;
    for (auto &kv : pe) { // multiply by the contribution from each prime
      int p = kv.first;
      long long e = kv.second;
      if (p == 2) {
        ans = ans * pow_inv(2, e) % MOD; // special case for prime 2
      } else {
        ans = ans * (p - 1) % MOD;
        ans = ans * pow_inv(p, e) % MOD; // adjust for other primes
      }
    }
    unordered_map<int, long long> Aq; // auxiliary map for prime factor computation
    Aq.reserve(128);
    for (auto &kv : pe) {
      int p = kv.first;
      if (p == 2)
        continue; // skip prime 2 as already handled
      int t = p - 1; // compute (p-1) to factorize in next loop
      while (t > 1) {
        int q = spf[t]; // find smallest prime factor of t
        int c = 0;
        while (t % q == 0) {
          t /= q;
          ++c;
        }
        Aq[q] += c; // accumulate counts for primes in (p-1) decomposition
      }
    }
    for (auto &kv : Aq) { // adjust the answer based on Carmichael function properties
      int q = kv.first;
      long long A = kv.second;
      if (pe.count(q)) {
        ans = ans * pow_inv(q, A) % MOD; // if q divides m, it's included in product
      } else {
        long long invq = inv[q];
        long long one_minus_invq = (1 - invq + MOD) % MOD;
        long long q_negA = pow_inv(q, A);
        long long term = (invq + one_minus_invq * q_negA) % MOD; // formula for non-dividing prime
        ans = ans * term % MOD;
      }
    }
    cout << ans % MOD << '\n'; // output final result modulo MOD
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/