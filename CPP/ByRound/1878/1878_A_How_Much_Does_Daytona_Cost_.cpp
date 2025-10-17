/*
 * Problem URL : https://codeforces.com/problemset/problem/1878/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    bool res(false);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x == k) {
        res = true;
      }
    }

    puts(res ? "YES" : "NO");
  }
}
