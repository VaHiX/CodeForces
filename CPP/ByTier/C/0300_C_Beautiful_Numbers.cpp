/*
 * Problem URL : https://codeforces.com/problemset/problem/300/C
 * Submit Date : 2025-08-16
 */

#include <cstdio>
#include <vector>
typedef long long ll;

bool checkDigits(long x, int a, int b) {
  while (x > 0) {
    int d = x % 10;
    x /= 10;
    if ((d != a) && (d != b)) {
      return false;
    }
  }

  return true;
}

int main() {

  const ll M = 1000000007;

  int a, b;
  long n;
  scanf("%d %d %ld\n", &a, &b, &n);

  std::vector<ll> invMod(n + 1, 1);
  for (long p = 2; p <= n; p++) {
    invMod[p] = M - ((M / p) * invMod[M % p]) % M;
  }

  std::vector<ll> fact(n + 1, 1);
  for (long p = 1; p <= n; p++) {
    if (p > n - p) {
      fact[p] = fact[n - p];
      continue;
    }
    fact[p] = (((fact[p - 1] * (n - p + 1)) % M) * invMod[p]) % M;
  }

  ll total(0);
  for (long p = 0; p <= n; p++) {
    long x = p * a + (n - p) * b;
    if (!checkDigits(x, a, b)) {
      continue;
    }
    total += fact[p];
    total %= M;
  }

  printf("%lld\n", total);

  return 0;
}
