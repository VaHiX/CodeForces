/*
 * Problem URL : https://codeforces.com/problemset/problem/703/B
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define sc(a) scanf("%lld", &a)
#define f0(n) for (ll i = 0; i < n; i++)
#define f1(n) for (ll i = 1; i <= n; i++)

ll c[100005];
ll f[100005];

int main() {
  ll n, k, sm = 0, a, ans = 0;
  sc(n);
  sc(k);

  f1(n) {
    sc(c[i]);
    sm = sm + c[i];
  }
  f1(k) {
    sc(a);
    f[a] = 1;
    sm = sm - c[a];
    ans = ans + (sm * c[a]);
  }
  f1(n) {
    if (f[i] == 0 && f[(i % n) + 1] == 0)
      ans = ans + (c[i] * c[(i % n) + 1]);
  }
  printf("%lld\n", ans);
}