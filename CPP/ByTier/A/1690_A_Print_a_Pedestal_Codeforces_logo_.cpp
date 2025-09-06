/*
 * Problem URL : https://codeforces.com/problemset/problem/1690/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a, b, c;
    if (n % 3 == 0) {
      a = b = c = (n - 3) / 3;
      a += 1;
      b += 2;
    } else if (n % 3 == 1) {
      a = b = c = (n - 4) / 3;
      a += 1;
      b += 3;
    } else if (n % 3 == 2) {
      a = b = c = (n - 5) / 3;
      a += 2;
      b += 3;
    }
    printf("%ld %ld %ld\n", a, b, c);
  }
}
