/*
 * Problem URL : https://codeforces.com/contest/1174/problem/B
 * Submit Date : 2025-08-30
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  bool odd(0), even(0);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    if (a[p] % 2) {
      odd = true;
    } else {
      even = true;
    }
  }
  if (even && odd) {
    sort(a.begin(), a.end());
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", a[p]);
  }
  puts("");

  return 0;
}
