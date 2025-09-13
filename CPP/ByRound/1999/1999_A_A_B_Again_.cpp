/*
 * Problem URL : https://codeforces.com/problemset/problem/1999/A
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0);
    while (n) {
      s += n % 10;
      n /= 10;
    }
    printf("%ld\n", s);
  }
}
