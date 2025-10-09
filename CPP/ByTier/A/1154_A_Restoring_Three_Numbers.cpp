/*
 * Problem URL : https://codeforces.com/problemset/problem/1154/A
 * Submit Date : 2025-08-27
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  const long n = 4;
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  printf("%ld %ld %ld\n", a[n - 1] - a[0], a[n - 1] - a[1], a[n - 1] - a[2]);

  return 0;
}
