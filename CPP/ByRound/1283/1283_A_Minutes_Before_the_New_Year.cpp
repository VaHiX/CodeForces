/*
 * Problem URL : https://codeforces.com/contest/1283/problem/A
 * Submit Date : 2025-08-27
 */



#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long h, m;
    scanf("%ld %ld", &h, &m);
    long ans = (24 - h) * 60 - m;
    printf("%ld\n", ans);
  }

  return 0;
}
