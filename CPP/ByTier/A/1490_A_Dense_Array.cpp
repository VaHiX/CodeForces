/*
 * Problem URL : https://codeforces.com/problemset/problem/1490/A
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1490/A
 * Submit Date : 2025-08-22
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev;
    scanf("%ld", &prev);
    long cnt(0);
    for (long p = 1; p < n; p++) {
      long x;
      scanf("%ld", &x);
      long a = (x < prev) ? x : prev;
      long b = (x > prev) ? x : prev;
      while (2 * a < b) {
        a *= 2;
        ++cnt;
      }
      prev = x;
    }

    printf("%ld\n", cnt);
  }
}
