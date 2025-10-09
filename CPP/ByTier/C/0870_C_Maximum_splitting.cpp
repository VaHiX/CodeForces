/*
 * Problem URL : https://codeforces.com/contest/870/problem/C
 * Submit Date : 2025-09-12
 */

#include <cstdio>

int main() {

  long q;
  scanf("%ld", &q);
  while (q--) {
    long n;
    scanf("%ld", &n);
    long div = n / 4;
    if (n <= 3 || n == 5 || n == 7 || n == 11) {
      puts("-1");
      continue;
    }
    if (n & 1) {
      --div;
    }
    printf("%ld\n", div);
  }

  return 0;
}
