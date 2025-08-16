/*
 * Problem URL : https://codeforces.com/problemset/problem/1996/A
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", (n / 4) + (n % 4) / 2);
  }
}
