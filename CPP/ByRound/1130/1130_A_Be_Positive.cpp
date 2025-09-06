/*
 * Problem URL : https://codeforces.com/contest/1130/problem/A
 * Submit Date : 2025-08-28
 */



#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long neg(0), pos(0);
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    if (a > 0) {
      ++pos;
    } else if (a < 0) {
      ++neg;
    }
  }

  if (pos >= (n + 1) / 2) {
    puts("1");
  } else if (neg >= (n + 1) / 2) {
    puts("-1");
  } else {
    puts("0");
  }

  return 0;
}
