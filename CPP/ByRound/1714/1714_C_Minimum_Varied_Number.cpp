/*
 * Problem URL : https://codeforces.com/problemset/problem/1714/C
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long s;
    scanf("%ld", &s);
    long long res(0);
    long long pow(1);
    for (long p = 9; p > 0; p--) {
      if (p > s) {
        continue;
      }
      res += pow * p;
      pow *= 10;
      s -= p;
    }

    printf("%lld\n", res);
  }
}
