/*
 * Problem URL : https://codeforces.com/problemset/problem/1625/B
 * Submit Date : 2025-08-16
 */

#include <cstdio>
#include <map>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> pos;
    long md(n + 1);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (pos.count(x)) {
        md = (md < (p - pos[x]) ? md : (p - pos[x]));
      }
      pos[x] = p;
    }

    printf("%ld\n", n - md);
  }
}
