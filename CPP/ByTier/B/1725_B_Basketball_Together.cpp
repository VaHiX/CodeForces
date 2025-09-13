/*
 * Problem URL : https://codeforces.com/problemset/problem/1725/B
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long n, d;
  scanf("%ld %ld", &n, &d);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.rbegin(), a.rend());
  long rem(n), ans(0);
  for (long p = 0; p < n; p++) {
    long x = a[p];
    long num = 1 + d / x;
    if (num <= rem) {
      rem -= num;
      ++ans;
    } else {
      break;
    }
  }

  printf("%ld\n", ans);
}
