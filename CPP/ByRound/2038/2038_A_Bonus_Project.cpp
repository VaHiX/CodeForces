/*
 * Problem URL : https://codeforces.com/problemset/problem/2038/A
 * Submit Date : 2025-08-10
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }

  std::vector<long> c(n, 0);
  long rem(k);
  for (long p = n - 1; p >= 0; p--) {
    long w = a[p] / b[p];
    c[p] = (w < rem ? w : rem);
    rem -= c[p];
  }

  for (long p = 0; p < n; p++) {
    printf("%ld ", rem ? 0 : c[p]);
  }
  puts("");

  return 0;
}
