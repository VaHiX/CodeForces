/*
 * Problem URL : https://codeforces.com/problemset/problem/222/D
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n, x;
  scanf("%ld %ld", &n, &x);
  std::vector<long> a(n), b(n);

  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  long count(0);
  for (long p = 0, q = n - 1; p < n && q >= 0; p++) {
    if (a[p] + b[q] >= x) {
      q--;
      count++;
    }
  }
  printf("1 %ld\n", count);

  return 0;
}
