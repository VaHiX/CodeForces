/*
 * Problem URL : https://codeforces.com/contest/1355/problem/B
 * Submit Date : 2025-09-11
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
    long cnt(0), cur(0);
    for (long p = 0; p < n; p++) {
      ++cur;
      if (a[p] <= cur) {
        ++cnt;
        cur = 0;
      }
    }

    printf("%ld\n", cnt);
  }

  return 0;
}
