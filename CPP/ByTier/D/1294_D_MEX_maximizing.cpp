/*
 * Problem URL : https://codeforces.com/contest/1294/problem/D
 * Submit Date : 2025-09-11
 */

#include <cstdio>
#include <vector>

int main() {

  long n, x;
  scanf("%ld %ld", &n, &x);
  std::vector<long> f(x, 0);
  long cnt(0);
  for (long p = 0; p < n; p++) {
    long y;
    scanf("%ld", &y);
    ++f[y % x];
    while (f[cnt % x] > (cnt / x)) {
      ++cnt;
    }
    printf("%ld\n", cnt);
  }

  return 0;
}
