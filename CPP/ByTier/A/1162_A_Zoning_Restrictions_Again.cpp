/*
 * Problem URL : https://codeforces.com/problemset/problem/1162/A
 * Submit Date : 2025-08-13
 */

#include <cstdio>
#include <vector>

int main() {

  long n, h, m;
  scanf("%ld %ld %ld", &n, &h, &m);
  std::vector<long> a(n, h);
  while (m--) {
    long l, r, x;
    scanf("%ld %ld %ld", &l, &r, &x);
    for (long p = l - 1; p < r; p++) {
      a[p] = (a[p] < x) ? a[p] : x;
    }
  }

  long long total(0);
  for (long p = 0; p < n; p++) {
    total += a[p] * a[p];
  }
  printf("%lld\n", total);

  return 0;
}
