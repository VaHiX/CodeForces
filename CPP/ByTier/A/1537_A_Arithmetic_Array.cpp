/*
 * Problem URL : https://codeforces.com/problemset/problem/1537/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x;
    }
    printf("%ld\n", (s >= n) ? (s - n) : 1);
  }
}
