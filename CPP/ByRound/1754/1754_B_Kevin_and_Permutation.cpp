/*
 * Problem URL : https://codeforces.com/problemset/problem/1754/B
 * Submit Date : 2025-08-13
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    for (long p = n / 2; p > 0; p--) {
      printf("%ld %ld ", p, p + (n / 2));
    }
    if (n % 2) {
      printf("%ld", n);
    }
    puts("");
  }
}
