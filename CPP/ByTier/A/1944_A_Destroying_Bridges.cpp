/*
 * Problem URL : https://codeforces.com/problemset/problem/1944/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    printf("%ld\n", k >= n - 1 ? 1 : n);
  }
}
