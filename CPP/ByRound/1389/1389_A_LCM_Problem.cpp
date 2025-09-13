/*
 * Problem URL : https://codeforces.com/contest/1389/problem/A
 * Submit Date : 2025-08-25
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long l, r;
    scanf("%ld %ld", &l, &r);
    if (2 * l > r) {
      puts("-1 -1");
    } else {
      printf("%ld %ld\n", l, 2 * l);
    }
  }

  return 0;
}
