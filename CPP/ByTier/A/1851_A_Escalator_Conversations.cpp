/*
 * Problem URL : https://codeforces.com/problemset/problem/1851/A
 * Submit Date : 2025-08-16
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k, H;
    scanf("%ld %ld %ld %ld", &n, &m, &k, &H);
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long u;
      scanf("%ld", &u);
      long diff = H - u;
      if (!diff || diff % k) {
        continue;
      }
      if (diff < 0) {
        diff = -diff;
      }

      cnt += (diff < m * k);
    }

    printf("%ld\n", cnt);
  }
}
