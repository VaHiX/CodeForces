/*
 * Problem URL : https://codeforces.com/contest/1256/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>
typedef long long ll;

int main() {

  ll q;
  scanf("%lld", &q);
  while (q--) {
    ll a, b, n, s;
    scanf("%lld %lld %lld %lld", &a, &b, &n, &s);
    bool ans = (n * a + b >= s) && (b >= s % n);
    puts(ans ? "YES" : "NO");
  }

  return 0;
}
