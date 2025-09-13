/*
 * Problem URL : https://codeforces.com/problemset/problem/2020/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    if (k == 1) {
      printf("%ld\n", n);
      continue;
    }
    long cnt(0);
    while (n) {
      cnt += n % k;
      n /= k;
    }
    printf("%ld\n", cnt);
  }
}
