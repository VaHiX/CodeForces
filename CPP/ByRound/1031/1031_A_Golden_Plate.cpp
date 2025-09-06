/*
 * Problem URL : https://codeforces.com/contest/1031/problem/A
 * Submit Date : 2025-08-30
 */



#include <cstdio>

int main() {

  long w, h, k;
  scanf("%ld %ld %ld", &w, &h, &k);
  long sum(0);
  while (k--) {
    sum += 2 * (w + h) - 4;
    w -= 4;
    h -= 4;
  }
  printf("%ld\n", sum);

  return 0;
}
