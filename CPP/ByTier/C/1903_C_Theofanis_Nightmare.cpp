/*
 * Problem URL : https://codeforces.com/problemset/problem/1903/C
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    long long suffix(0), total(0);
    for (long p = n - 1; p >= 0; p--) {
      suffix += v[p];
      total += suffix * (suffix > 0);
    }

    total += suffix * (suffix < 0);
    printf("%lld\n", total);
  }
}
