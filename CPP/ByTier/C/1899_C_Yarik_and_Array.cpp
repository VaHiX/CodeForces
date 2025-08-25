/*
 * Problem URL : https://codeforces.com/problemset/problem/1899/C
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);

    long prev(0), cs(0), mxs(-1007);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if ((prev + x) % 2 == 0 || cs < 0) {
        cs = 0;
      }
      cs += x;
      mxs = (mxs > cs ? mxs : cs);
      prev = (x % 2);
    }

    printf("%ld\n", mxs);
  }
}
