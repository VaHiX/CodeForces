/*
 * Problem URL : https://codeforces.com/contest/1056/problem/A
 * Submit Date : 2025-08-30
 */

#include <cstdio>
#include <vector>

int main() {

  const int N = 107;
  long n;
  scanf("%ld", &n);
  std::vector<long> a(N, 0);
  for (long p = 0; p < n; p++) {
    long k;
    scanf("%ld", &k);
    while (k--) {
      long x;
      scanf("%ld", &x);
      ++a[x];
    }
  }

  for (long p = 0; p < N; p++) {
    if (a[p] == n) {
      printf("%ld ", p);
    }
  }
  puts("");

  return 0;
}
