/*
 * Problem URL : https://codeforces.com/contest/802/problem/M
 * Submit Date : 2025-09-08
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
  sort(a.begin(), a.end());
  long sum(0);
  for (long p = 0; p < k; p++) {
    sum += a[p];
  }
  printf("%ld\n", sum);

  return 0;
}
