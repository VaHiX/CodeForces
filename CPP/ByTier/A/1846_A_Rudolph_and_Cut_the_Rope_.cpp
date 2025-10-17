/*
 * Problem URL : https://codeforces.com/problemset/problem/1846/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(0);
    for (long p = 0; p < n; p++) {
      long a, b;
      scanf("%ld %ld", &a, &b);
      cnt += (a > b);
    }

    printf("%ld\n", cnt);
  }
}
