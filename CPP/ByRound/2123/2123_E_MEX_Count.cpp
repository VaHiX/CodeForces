/*
 * Problem URL : https://codeforces.com/problemset/problem/2123/E
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), ans(n + 1), diff(n + 2), freq(n + 2);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++freq[x];
    }
    for (long p = 0; p <= n; p++) {
      ++diff[freq[p]];
      --diff[n - p + 1];
      if (!freq[p]) {
        break;
      }
    }

    long cs(0);
    for (long p = 0; p <= n; p++) {
      cs += diff[p];
      printf("%ld ", cs);
    }
    puts("");
  }
}
