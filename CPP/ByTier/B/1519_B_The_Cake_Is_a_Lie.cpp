/*
 * Problem URL : https://codeforces.com/problemset/problem/1519/B
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, k;
    scanf("%ld %ld %ld", &n, &m, &k);
    bool res = (n * m - 1 == k);
    puts(res ? "YES" : "NO");
  }
}
