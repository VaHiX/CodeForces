/*
 * Problem URL : https://codeforces.com/contest/1485/problem/B
 * Submit Date : 2025-08-27
 */

#include <cstdio>
#include <vector>

int main() {

  long n, q, k;
  scanf("%ld %ld %ld", &n, &q, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  while (q--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long ans = k + (a[r - 1] - a[l - 1] + 1) - 2 * (r - l + 1);
    printf("%ld\n", ans);
  }
}
