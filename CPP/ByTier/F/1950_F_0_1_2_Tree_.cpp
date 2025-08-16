/*
 * Problem URL : https://codeforces.com/problemset/problem/1950/F
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    if (c != a + 1) {
      puts("-1");
      continue;
    }
    if (!a && !b) {
      puts("0");
      continue;
    }

    long cur(1), nxt(0), depth(1);
    for (long p = 0; p < a + b; p++) {
      if (!cur) {
        cur = nxt;
        nxt = 0;
        ++depth;
      }
      --cur;
      nxt += 1 + (p < a);
    }

    printf("%ld\n", depth);
  }
}
