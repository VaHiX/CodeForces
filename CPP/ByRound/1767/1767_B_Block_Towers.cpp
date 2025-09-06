/*
 * Problem URL : https://codeforces.com/problemset/problem/1767/B
 * Submit Date : 2025-08-20
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
    long x;
    scanf("%ld", &x);

    std::vector<long> a(n - 1);
    for (long p = 0; p + 1 < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());

    for (long p = 0; p + 1 < n; p++) {
      if (a[p] <= x) {
        continue;
      }
      x = (a[p] + x + 1) / 2;
    }

    printf("%ld\n", x);
  }
}
