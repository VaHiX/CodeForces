/*
 * Problem URL : https://codeforces.com/problemset/problem/2095/E
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3fLL;
const int MAX = 1e4 + 10;
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll g, tmp;
  g = exgcd(b, a % b, x, y);
  tmp = x;
  x = y;
  y = tmp - a / b * y;
  return g;
}
ll inv_exgcd(ll a, ll p) {
  ll g, x, y;
  g = exgcd(a, p, x, y);
  return g == 1 ? (x % p + p) % p : -1;
}
int main() {
  int n, k, p, i, x, cntk, cnt0;
  ll ans, tmp;
  scanf("%d%d%d", &n, &p, &k);
  map<int, int> mp;
  cnt0 = 0;
  ans = 0;
  for (i = 1; i <= n; i++) {
    scanf("%d", &x);
    if (x == 0)
      cnt0++;
    tmp = inv_exgcd(1LL * x * x % p * x % p, p);
    if (tmp == -1)
      continue;
    tmp = tmp * k % p;
    if (mp.count(tmp))
      ans += mp[tmp];
    mp[1LL * x * x % p * x % p]++;
  }
  if (k == 0)
    ans += 1LL * cnt0 * (n - cnt0);
  printf("%lld\n", ans);
  return 0;
}
/*
ai^3 * aj^3 = k (mod p)
*/