/*
 * Problem URL : https://codeforces.com/problemset/problem/1995/A
 * Submit Date : 2025-08-11
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (!k) {
      puts("0");
      continue;
    }
    k -= n;
    long cnt(1);
    for (long p = n - 1; k > 0 && p > 0; p--) {
      k -= p;
      ++cnt;
      if (k > 0) {
        k -= p;
        ++cnt;
      }
    }

    printf("%ld\n", cnt);
  }
}
