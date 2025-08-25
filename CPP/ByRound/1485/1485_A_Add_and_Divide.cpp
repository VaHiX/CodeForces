/*
 * Problem URL : https://codeforces.com/contest/1485/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1485/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long res(1 + a / b);
    for (long p = b; p <= b + 100; p++) {
      if (p == 1) {
        continue;
      }
      long div(0), cur(a);
      while (cur) {
        cur /= p;
        ++div;
      }
      long cnt = (p - b) + div;
      res = (res < cnt) ? res : cnt;
    }

    printf("%ld\n", res);
  }
}
