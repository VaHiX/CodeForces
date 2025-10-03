/*
 * Problem URL : https://codeforces.com/contest/1675/problem/B
 * Submit Date : 2025-08-28
 */

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
    long cnt(0);
    for (long p = n - 2; p >= 0; p--) {
      if (a[p + 1] <= 0) {
        cnt = -1;
        break;
      }
      while (a[p] >= a[p + 1]) {
        a[p] /= 2;
        ++cnt;
      }
    }

    printf("%ld\n", cnt);
  }
}
