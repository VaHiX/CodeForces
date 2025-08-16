/*
 * Problem URL : https://codeforces.com/problemset/problem/1926/C
 * Submit Date : 2025-08-12
 */

#include <cstdio>
#include <vector>

long sumdigits(long x) {
  long s(0);
  while (x) {
    s += (x % 10);
    x /= 10;
  }
  return s;
}

int main() {

  const long N = 200007;

  std::vector<long> v(N, 0);
  for (long p = 1; p < N; p++) {
    v[p] = v[p - 1] + sumdigits(p);
  }

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    printf("%ld\n", v[n]);
  }
}
