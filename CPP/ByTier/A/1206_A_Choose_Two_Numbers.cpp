/*
 * Problem URL : https://codeforces.com/problemset/problem/1206/A
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long sa(0);
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    sa = (sa > a) ? sa : a;
  }
  long m;
  scanf("%ld", &m);
  long sb(0);
  for (long p = 0; p < m; p++) {
    long b;
    scanf("%ld", &b);
    sb = (sb > b) ? sb : b;
  }
  printf("%ld %ld\n", sa, sb);

  return 0;
}
