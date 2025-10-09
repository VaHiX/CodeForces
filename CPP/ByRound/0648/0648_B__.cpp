/*
 * Problem URL : https://codeforces.com/contest/648/problem/B
 * Submit Date : 2025-09-11
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(2 * n);
  for (long p = 0; p < 2 * n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  for (long p = 0; p < n; p++) {
    printf("%ld %ld\n", a[p], a[2 * n - 1 - p]);
  }
  puts("");
}
