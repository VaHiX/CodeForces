/*
 * Problem URL : https://codeforces.com/problemset/problem/2102/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, p, q;
    scanf("%ld %ld %ld %ld", &n, &m, &p, &q);
    puts((n % p) || (n * q == m * p) ? "YES" : "NO");
  }
}
