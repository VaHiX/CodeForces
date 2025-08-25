/*
 * Problem URL : https://codeforces.com/problemset/problem/1827/A
 * Submit Date : 2025-08-18
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long long MOD = 1e9 + 7;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    };
    sort(a.begin(), a.end());
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    };
    sort(b.begin(), b.end());

    long idx(n - 1);
    long long res(1);
    for (long p = n - 1; p >= 0; p--) {
      while (idx >= 0 && a[idx] > b[p]) {
        --idx;
      }
      long diff = p - idx;
      if (diff < 0) {
        res = 0;
        break;
      }
      res *= diff;
      res %= MOD;
    }

    printf("%lld\n", res);
  }
}
