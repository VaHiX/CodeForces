/*
 * Problem URL : https://codeforces.com/problemset/problem/1918/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    printf("%ld\n", n * (m / 2));
  }
}
