/*
 * Problem URL : https://codeforces.com/problemset/problem/1165/B
 * Submit Date : 2025-08-13
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
  long cur(0);
  for (long p = 0; p < n; p++) {
    if (a[p] >= cur + 1) {
      ++cur;
    }
  }
  printf("%ld\n", cur);

  return 0;
}
