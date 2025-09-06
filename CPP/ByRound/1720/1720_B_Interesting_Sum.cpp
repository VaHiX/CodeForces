/*
 * Problem URL : https://codeforces.com/problemset/problem/1720/B
 * Submit Date : 2025-08-21
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    long ans = a[n - 1] + a[n - 2] - a[0] - a[1];
    printf("%ld\n", ans);
  }
}
