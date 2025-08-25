/*
 * Problem URL : https://codeforces.com/problemset/problem/2061/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  const long MOD = 998244353;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n + 1), f(n + 1, 0);
    for (long p = 1; p <= n; p++) {
      scanf("%ld", &a[p]);
    }

    f[0] = 1;
    for (long p = 1; p <= n; p++) {
      f[p] = (a[p - 1] == a[p]) * f[p - 1] +
             (p > 1 && a[p - 2] + 1 == a[p]) * f[p - 2];
      f[p] %= MOD;
    }

    long ans = (f[n - 1] + f[n]) % MOD;
    printf("%ld\n", ans);
  }
}
