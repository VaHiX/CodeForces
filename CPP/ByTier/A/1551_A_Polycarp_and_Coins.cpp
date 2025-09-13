/*
 * Problem URL : https://codeforces.com/problemset/problem/1551/A
 * Submit Date : 2025-08-18
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long d = n / 3;
    printf("%ld %ld\n", d + (n % 3 == 1), d + (n % 3 == 2));
  }
}
