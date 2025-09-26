/*
 * Problem URL : https://codeforces.com/problemset/problem/1787/A
 * Submit Date : 2025-08-20
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    if (n % 2) {
      puts("-1");
    } else {
      printf("%ld 1\n", n / 2);
    }
  }
}
