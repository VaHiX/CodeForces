/*
 * Problem URL : https://codeforces.com/contest/1359/problem/A
 * Submit Date : 2025-08-26
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long x = (n / k);
    long a = (x < m) ? x : m;
    long b = ((m - a) + (k - 2)) / (k - 1);
    long res = a - b;
    printf("%ld\n", res);
  }

  return 0;
}
