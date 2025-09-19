/*
 * Problem URL : https://codeforces.com/contest/338/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
using namespace std;

typedef int64_t ll;
const ll M = 1e9 + 9;

ll binpow(ll n, ll pw) {
  if (pw == 0)
    return 1ll;
  if (pw & 1) {
    return n * binpow(n, pw - 1) % M;
  } else {
    ll p = binpow(n, pw / 2);
    return p * p % M;
  }
}

signed main() {
  ll n, m, k;
  cin >> n >> m >> k;
  ll C = max(0ll, m - (n - n % k) / k * (k - 1) - n % k);
  ll ans = (binpow(2ll, C + 1) - 2) * k % M;
  ans = (ans + (m - C * k) % M + M) % M;
  cout << ans << '\n';
} /*1691585761.8128688*/