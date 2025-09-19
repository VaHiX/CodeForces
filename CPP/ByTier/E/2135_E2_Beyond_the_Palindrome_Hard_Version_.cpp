/*
 * Problem URL : https://codeforces.com/contest/2135/problem/E2
 * Submit Date : 2025-08-30
 */

#include <bits/stdc++.h>
using namespace std;

using LL = long long;
const int MOD = 998244353;
const int LIM = 20000000 + 10;

inline int addmod(int a, int b) {
  a += b;
  return a >= MOD ? a - MOD : a;
}
inline int submod(int a, int b) {
  a -= b;
  return a < 0 ? a + MOD : a;
}
inline void inc(int &a, int b) {
  a += b;
  if (a >= MOD)
    a -= MOD;
}
inline void dec(int &a, int b) {
  a -= b;
  if (a < 0)
    a += MOD;
}

int prime[LIM], tot;
int F[LIM], G[LIM];
int fact[LIM], invfact[LIM];

int modexp(int b, int e) {
  int res = 1;
  while (e) {
    if (e & 1)
      res = (LL)res * b % MOD;
    b = (LL)b * b % MOD;
    e >>= 1;
  }
  return res;
}

void preprocess(int n) {
  F[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!F[i]) {
      prime[++tot] = i;
      F[i] = G[i] = i + (i > 2);
    }
    for (int j = 1; j <= tot; j++) {
      int p = prime[j];
      if (1LL * i * p > n)
        break;
      if (i % p == 0) {
        G[i * p] = G[i] * p + (j > 1);
        F[i * p] = F[i] / G[i] * G[i * p];
        break;
      }
      F[i * p] = F[i] * (p + (j > 1));
      G[i * p] = p + (j > 1);
    }
  }
  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = (LL)fact[i - 1] * i % MOD;
  invfact[n] = modexp(fact[n], MOD - 2);
  for (int i = n; i >= 1; i--)
    invfact[i - 1] = (LL)invfact[i] * i % MOD;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  preprocess(20000001); // FIX: matches your original `init(2e7 + 1)`

  while (T--) {
    int n;
    cin >> n;
    int res = 0;
    for (int i = 0; i <= n; i++) {
      int coef = (LL)invfact[i] * invfact[n - i] % MOD;
      int diff = submod(F[abs(n - 2 * i - 1)], F[abs(n - 2 * i)]);
      res = (res + (LL)coef * diff) % MOD;
    }
    res = (LL)res * fact[n] % MOD;
    res = addmod(res, res);
    if (n & 1)
      inc(res, modexp(2, n));
    else
      dec(res, modexp(2, n));
    cout << res << "\n";
  }
  return 0;
}
