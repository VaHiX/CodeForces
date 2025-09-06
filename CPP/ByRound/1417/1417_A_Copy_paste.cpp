/*
 * Problem URL : https://codeforces.com/contest/1417/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1417/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    long idx(0);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] < a[idx]) {
        idx = p;
      }
    }

    long long cnt(0);
    for (long p = 0; p < n; p++) {
      if (p == idx) {
        continue;
      }
      cnt += (k - a[p]) / a[idx];
    }
    printf("%lld\n", cnt);
  }

  return 0;
}
