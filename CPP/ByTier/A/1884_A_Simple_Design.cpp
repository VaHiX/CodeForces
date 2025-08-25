/*
 * Problem URL : https://codeforces.com/problemset/problem/1884/A
 * Submit Date : 2025-08-15
 */

#include <cstdio>

long digsum(long x) {
  long res(0);
  while (x > 0) {
    res += x % 10;
    x /= 10;
  }
  return res;
}

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, k;
    scanf("%ld %ld", &x, &k);
    long res(x);
    while (digsum(x) % k) {
      ++x;
    }
    printf("%ld\n", x);
  }
}
