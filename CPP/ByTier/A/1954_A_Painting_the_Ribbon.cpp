/*
 * Problem URL : https://codeforces.com/problemset/problem/1954/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    long need = (m - 1) * (n / m) + (n % m > 0) * (n % m - 1);
    puts(k < need ? "YES" : "NO");
  }
}
