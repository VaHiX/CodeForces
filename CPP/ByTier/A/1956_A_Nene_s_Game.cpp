/*
 * Problem URL : https://codeforces.com/problemset/problem/1956/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long k, q;
    scanf("%ld %ld", &k, &q);
    long a;
    scanf("%ld", &a);
    --a;
    long x;
    while (--k) {
      scanf("%ld", &x);
    }
    while (q--) {
      scanf("%ld", &x);
      printf("%ld ", a < x ? a : x);
    }
    puts("");
  }
}
