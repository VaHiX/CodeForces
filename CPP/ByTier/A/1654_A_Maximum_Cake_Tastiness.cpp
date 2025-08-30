/*
 * Problem URL : https://codeforces.com/problemset/problem/1654/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mxa(0), mxb(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x >= mxa) {
        mxb = mxa;
        mxa = x;
      } else if (x > mxb) {
        mxb = x;
      }
    }

    printf("%ld\n", mxa + mxb);
  }
}
