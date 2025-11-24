// Problem: CF 1821 F - Timber
// https://codeforces.com/contest/1821/problem/F

/*
Code Purpose:
This solution calculates the number of "unfortunate" alleys where m trees of
height k can be chopped down such that no tree falls on the mall (index 0) or
road (index n+1), and each spot is covered by at most one tree. The algorithm
uses inclusion-exclusion principle combined with combinatorics to compute the
count.

Algorithms/Techniques:
- Inclusion-Exclusion Principle
- Combinatorial mathematics (binomial coefficients)
- Modular arithmetic and modular exponentiation
- Preprocessing factorials and their modular inverses

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <ctype.h>
#include <iostream>
#include <stdio.h>

#define m_p(a, b) make_pair(a, b)
#define pb(a) push_back(a)
#define ll long long
#define ull unsigned long long
#define inf 0x7FFFFFFF
#define inff 9223372036854775807
#define rep(i, l, r) for (int i = l; i < r; ++i)
#define repp(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, r, l) for (int i = r - 1; i >= l; --i)
#define pii pair<int, int>
#define fi first
#define se second
#define p_q priority_queue
#define Kill(x)                                                                \
  {                                                                            \
    cout << x << endl;                                                         \
    return 0;                                                                  \
  }
#define all(x) x.begin(), x.end()
#define mod 998244353
#define int ll
using namespace std;
inline int rd() {
  int x(0), f(1);
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      f = -f;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
inline void out(int X) {
  if (X < 0) {
    X = ~(X - 1);
    putchar('-');
  }
  if (X > 9)
    out(X / 10);
  putchar(X % 10 + '0');
}
ll pw(int x, int d) {
  if (!d)
    return 1;
  ll t = pw(x, d >> 1);
  t = t * t % mod;
  if (d & 1)
    return t * x % mod;
  return t;
}
#define MAX 300005
ll jie[MAX]; // Factorial array
ll inv[MAX]; // Modular inverse of factorial
ll pw2[MAX]; // Powers of 2 modulo mod
inline ll Comb(int x, int y) {
  if (y > x)
    return 0;
  return jie[x] * inv[x - y] % mod * inv[y] % mod;
}
signed main() {
  int n = rd();
  int m = rd();
  int k = rd();
  jie[0] = 1;
  rep(i, 1, MAX) jie[i] = (jie[i - 1] * i) % mod;
  inv[MAX - 1] = pw(jie[MAX - 1], mod - 2);
  per(i, MAX - 1, 0) inv[i] = (inv[i + 1] * (i + 1)) % mod;
  pw2[0] = 1;
  rep(i, 1, MAX) pw2[i] = (pw2[i - 1] << 1) % mod;
  int nw = 1;
  ll ans = 0;
  repp(i, 0, m) {
    ans = (ans +
           pw2[m - i] * nw % mod * Comb(n - m * k - i * k, m) % mod *
               Comb(m, i) % mod +
           mod) %
          mod;
    nw *= -1;
  }
  cout << ans << endl;
  return 0;
}

// https://github.com/VaHiX/CodeForces/