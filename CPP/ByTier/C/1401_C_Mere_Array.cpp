/*
 * Problem URL : https://codeforces.com/contest/1401/problem/C
 * Submit Date : 2025-08-29
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n), b(n);
    long mn(1e9 + 7);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      a[p] = x;
      b[p] = x;
      mn = (mn < x) ? mn : x;
    }

    sort(b.begin(), b.end());

    bool res(true);
    for (long p = 0; p < n; p++) {
      if (a[p] == b[p]) {
        continue;
      }
      if (a[p] % mn == 0) {
        continue;
      }
      res = false;
      break;
    }

    puts(res ? "YES" : "NO");
  }

  return 0;
}
