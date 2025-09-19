/*
 * Problem URL : https://codeforces.com/problemset/problem/678/D
 * Submit Date : 2025-08-19
 */

#include <cstdio>
typedef long long ll;

int main() {

  const ll MOD = 1e9 + 7;
  ll a, b, n, x;
  scanf("%lld %lld %lld %lld", &a, &b, &n, &x);
  while (n > 0) {
    if (n % 2) {
      x = (a * x + b) % MOD;
    }
    b *= (a + 1);
    b %= MOD;
    a *= a;
    a %= MOD;
    n /= 2;
  }

  printf("%lld\n", x);

  return 0;
}
