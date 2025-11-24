// Problem: CF 1954 F - Unique Strings
// https://codeforces.com/contest/1954/problem/F

/*
Code Purpose:
This code solves the problem of counting unique binary strings that can be formed from a given string of 1s and 0s, 
by replacing at most k 0s with 1s. The strings are considered equal if one can be obtained by cyclically shifting the other.
The solution uses Burnside's lemma and combinatorics to count distinct necklaces under rotation, with additional constraints on the number of operations.

Algorithms/Techniques:
- Burnside's Lemma: For counting distinct necklaces under rotation
- Combinatorics: Used for computing combinations C(n, k)
- Modular Exponentiation: For modular inverse calculations
- Memoization: To optimize recursive function computations

Time Complexity: O(n^2 * log(M)) where n is the length of the string and M is the modulo value.
Space Complexity: O(n) for storing precomputed factorials, inverse factorials, and memoization table.

*/
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>

using namespace std;
typedef long long ll;
#define M 1000000007
#define N 3000
int i, j, k, n, m, t, d;
ll jc[N + 50], inv[N + 50], p[N + 50], res, g[N + 50];
ll su(ll a, ll b) {
  a += b;
  return (a >= M) ? a - M : a;
}
ll ksm(ll a, ll p) {
  ll res = 1;
  while (p) {
    if (p & 1) {
      res = res * a % M;
    }
    a = a * a % M;
    p >>= 1;
  }
  return res;
}
ll c(ll n, ll m) {
  if (n < m || n < 0 || m < 0) {
    return 0;
  }
  return jc[n] * inv[m] % M * inv[n - m] % M;
}
map<ll, ll> f;
ll fuck(ll k, ll m, ll sz) {
  if (f.count(k))
    return f[k];
  ll res = 0, i, j;
  sz = min(sz, k);
  if (k == sz)
    res++;
  for (i = 1; i * m <= sz; i++) {
    ll t1 = (c(k - i * m, i) + m * c(k - i * m - 1, i - 1)) % M, t2 = 0;
    for (j = 0; j <= sz - i * m; j++)
      t2 += c(k - i * (m + 1), j);
    t1 = t1 * (t2 % M) % M;
    if (i & 1)
      res += t1;
    else
      res -= t1;
  }
  res = (res % M + M) % M;
  return f[k] = res;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  jc[0] = inv[0] = 1;
  for (i = 1; i <= N; i++)
    jc[i] = jc[i - 1] * i % M;
  inv[N] = ksm(jc[N], M - 2);
  for (i = N - 1; i >= 1; i--)
    inv[i] = inv[i + 1] * (i + 1) % M;
  cin >> n >> m >> t;
  for (i = 1; i <= n; i++) {
    k = gcd(i, n);
    res += fuck(k, m, (m + t) / (n / k));
    res %= M;
  }
  cout << res * ksm(n, M - 2) % M;
}


// https://github.com/VaHiX/CodeForces/