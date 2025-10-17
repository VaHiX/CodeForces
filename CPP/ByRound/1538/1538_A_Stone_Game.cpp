/*
 * Problem URL : https://codeforces.com/problemset/problem/1538/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e7), mx(-1e7);
    long wn(-1), wx(-1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x < mn) {
        mn = x;
        wn = p;
      }
      if (x > mx) {
        mx = x;
        wx = p;
      }
    }

    if (wn > wx) {
      long tmp = wn;
      wn = wx;
      wx = tmp;
    }
    long da = wx + 1;
    long db = n - wn;
    long dc = (n - wx + 1) + wn;

    long res = (da < db) ? da : db;
    res = res < dc ? res : dc;

    printf("%ld\n", res);
  }
}
