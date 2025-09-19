/*
 * Problem URL : https://codeforces.com/contest/1426/problem/D
 * Submit Date : 2025-09-10
 */

#include <cstdio>
#include <set>
typedef long long ll;

int main() {

  ll n;
  scanf("%lld", &n);
  std::set<ll> s;
  s.insert(0);
  ll acc(0), cnt(0);
  for (ll p = 0; p < n; p++) {
    ll x;
    scanf("%lld", &x);
    acc += x;
    if (s.count(acc)) {
      s.clear();
      s.insert(0);
      ++cnt;
      acc = x;
    }
    s.insert(acc);
  }

  printf("%lld\n", cnt);

  return 0;
}
