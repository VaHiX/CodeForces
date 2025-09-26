/*
 * Problem URL : https://codeforces.com/problemset/problem/1923/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long start(-1), z(0), cnt(0);
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x) {
        if (start < 0) {
          start = p;
        }
        cnt += z;
        z = 0;
      } else if (start >= 0) {
        ++z;
      }
    }

    printf("%ld\n", cnt);
  }
}
