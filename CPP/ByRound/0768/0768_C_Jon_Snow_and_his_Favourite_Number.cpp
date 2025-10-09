/*
 * Problem URL : https://codeforces.com/contest/768/problem/C
 * Submit Date : 2025-09-01
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {
  long n, k, x;
  scanf("%ld %ld %ld", &n, &k, &x);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }

  k %= 64;

  while (k--) {
    sort(a.begin(), a.end());
    for (int p = 0; p < n; p += 2) {
      a[p] ^= x;
    }
  }

  sort(a.begin(), a.end());
  printf("%ld %ld\n", a[n - 1], a[0]);

  return 0;
}
