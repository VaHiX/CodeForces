/*
 * Problem URL : https://codeforces.com/contest/1092/problem/B
 * Submit Date : 2025-08-31
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  long s(0);
  for (long p = 0; p < n - 1; p += 2) {
    s += a[p + 1] - a[p];
  }
  printf("%ld\n", s);

  return 0;
}
