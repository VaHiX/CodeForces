/*
 * Problem URL : https://codeforces.com/contest/806/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool check(ll x, ll y, ll p, ll q, ll t) {
  return p * t >= x && q * t - p * t >= y - x;
}

void solve() {
  ll x, y, p, q;
  scanf("%lld%lld%lld%lld", &x, &y, &p, &q);

  ll l = -1;
  ll r = (ll)1e9;

  if (!check(x, y, p, q, r)) {
    printf("-1\n");
    return;
  }

  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (check(x, y, p, q, m)) {
      r = m;
    } else {
      l = m;
    }
  }

  printf("%lld\n", r * q - y);
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    solve();
  }

  return 0;
}