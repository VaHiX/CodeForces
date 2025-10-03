/*
 * Problem URL : https://codeforces.com/contest/1912/problem/J
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define ll long long
int h;
ll t, s;
ll a, b, c;
ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
ll S(ll a, ll b, ll d) { // a<b d
  if (a > b)
    return 0;
  ll cnt = (b - a) / d + 1;
  return (a + b) * cnt / 2;
}
ll Suan(ll a, ll b, ll t) { // ak1+bk2<=t k1>=0 k2>=0
  if (t < 0)
    return 0;
  ll g = gcd(a, b);
  a /= g, b /= g, t /= g;
  ll ans = 0;
  for (int x = 0; x < b; x++) {
    if (t - a * x < 0)
      continue;
    ll tt = (t - a * x) / b;
    ans += S((tt + 1) % a, tt + 1, a);
  }
  return ans;
}
int main() {
  scanf("%d", &h);
  while (h--) {
    scanf("%lld%lld", &t, &s);
    unsigned long long ans = 0;
    if (s == 1) {
      scanf("%lld", &a);
      if (t % a == 0)
        ans = 1;
    } else if (s == 2) {
      scanf("%lld%lld", &a, &b);
      ans = Suan(a, b, t) - Suan(a, b, t - 1);
    } else {
      scanf("%lld%lld%lld", &a, &b, &c);
      for (ll x = 0; x < c; x++) {
        for (ll y = 0; y < c; y++) {
          if ((a * x + b * y - t) % c == 0) {
            ans += Suan(a, b, (t - a * x - b * y) / c);
          }
        }
      }
    }
    printf("%llu\n", ans);
  }
  return 0;
}