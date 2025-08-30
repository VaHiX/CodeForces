/*
 * Problem URL : https://codeforces.com/contest/1320/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>
#include <map>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::map<ll, ll> m;
  ll mx(0);
  for (ll p = 0; p < n; p++) {
    ll b;
    scanf("%lld", &b);
    m[b - p] += b;
    mx = (mx > m[b - p]) ? mx : m[b - p];
  }

  printf("%lld\n", mx);

  return 0;
}
