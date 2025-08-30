/*
 * Problem URL : https://codeforces.com/problemset/problem/2004/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    long L, R;
    scanf("%ld %ld", &L, &R);
    long mxl = (l > L ? l : L);
    long mnr = (r < R ? r : R);
    long len = (mnr - mxl);
    long res = len + (l != L) + (r != R);
    res = (len >= 0 ? res : 1);
    printf("%ld\n", res);
  }
}
