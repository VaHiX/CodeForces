/*
 * Problem URL : https://codeforces.com/problemset/problem/2051/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b, c;
    scanf("%ld %ld %ld %ld", &n, &a, &b, &c);
    long s(a + b + c);
    long t = 3 * (n / s);
    n %= s;
    if (0 < n && n <= a) {
      ++t;
    } else if (a < n && n <= a + b) {
      t += 2;
    } else if (n > a + b) {
      t += 3;
    }

    printf("%ld\n", t);
  }
}
