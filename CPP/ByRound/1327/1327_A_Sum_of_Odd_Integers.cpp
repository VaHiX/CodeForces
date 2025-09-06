/*
 * Problem URL : https://codeforces.com/contest/1327/problem/A
 * Submit Date : 2025-08-26
 */



#include <cstdio>
typedef long long ll;

int main() {

  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    bool res = (n % 2 == k % 2) && (n >= k * k);
    puts(res ? "YES" : "NO");
  }

  return 0;
}
