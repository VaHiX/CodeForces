/*
 * Problem URL : https://codeforces.com/problemset/problem/996/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long mint(1e9 + 7), entry(-1);
  for (long p = 0; p < n; p++) {
    long cand = p + n * ((a[p] - p + (n - 1)) / n);

    if (cand < mint) {
      mint = cand;
      entry = p;
    }
  }

  printf("%ld\n", 1 + entry);

  return 0;
}
