/*
 * Problem URL : https://codeforces.com/problemset/problem/2031/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <map>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> m;
    long mxcnt(0);
    for (long p = 0; p < n; p++) {
      long h;
      scanf("%ld", &h);
      ++m[h];
      mxcnt = (mxcnt > m[h] ? mxcnt : m[h]);
    }

    printf("%ld\n", n - mxcnt);
  }
}
