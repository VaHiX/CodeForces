/*
 * Problem URL : https://codeforces.com/problemset/problem/1668/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    long x = (m < n) ? m : n;
    long y = (m > n) ? m : n;
    if (x == 1 && y >= 3) {
      puts("-1");
    } else {
      printf("%ld\n", 2 * (y - 1) - (x + y) % 2);
    }
  }
}
