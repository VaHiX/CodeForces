/*
 * Problem URL : https://codeforces.com/contest/1407/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1407/A
 * Submit Date : 2025-08-23
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
      long x;
      scanf("%ld", &x);
      cnt += x;
    }
    if (cnt <= n / 2) {
      printf("%ld\n", n / 2);
      for (long p = 0; p < n / 2; p++) {
        printf("0 ");
      };
    } else {
      cnt -= (cnt % 2);
      printf("%ld\n", cnt);
      for (long p = 0; p < cnt; p++) {
        printf("1 ");
      };
    }
    puts("");
  }

  return 0;
}
