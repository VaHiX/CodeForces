/*
 * Problem URL : https://codeforces.com/problemset/problem/1555/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    n = (n > 6) ? n : 6;
    ll res = (n + 1) / 2 * 5;
    printf("%lld\n", res);
  }
}
