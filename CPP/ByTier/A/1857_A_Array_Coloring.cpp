/*
 * Problem URL : https://codeforces.com/problemset/problem/1857/A
 * Submit Date : 2025-08-16
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1857/A
 * Submit Date : 2025-08-16
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
    puts(s % 2 ? "NO" : "YES");
  }
}
