/*
 * Problem URL : https://codeforces.com/contest/1487/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1487/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(107), cnt(0);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (a < mn) {
        mn = a;
        cnt = 1;
      } else if (a == mn) {
        ++cnt;
      }
    }

    printf("%ld\n", n - cnt);
  }
}
