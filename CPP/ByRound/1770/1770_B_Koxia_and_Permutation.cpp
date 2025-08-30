/*
 * Problem URL : https://codeforces.com/problemset/problem/1770/B
 * Submit Date : 2025-08-19
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    long left(1), right(n);
    for (long p = 1; p <= n; p++) {
      if (p % 2) {
        printf("%ld ", right);
        --right;
      } else {
        printf("%ld ", left);
        ++left;
      }
    }

    puts("");
  }
}
