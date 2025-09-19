/*
 * Problem URL : https://codeforces.com/contest/1059/problem/A
 * Submit Date : 2025-08-30
 */

#include <cstdio>

int main() {

  long n, L, a;
  scanf("%ld %ld %ld", &n, &L, &a);
  long cur(0), cnt(0);
  while (n--) {
    long t, l;
    scanf("%ld %ld", &t, &l);
    cnt += (t - cur) / a;
    cur = t + l;
  }

  cnt += (L - cur) / a;

  printf("%ld\n", cnt);

  return 0;
}
