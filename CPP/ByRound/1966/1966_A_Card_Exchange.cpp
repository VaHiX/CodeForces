/*
 * Problem URL : https://codeforces.com/problemset/problem/1966/A
 * Submit Date : 2025-08-12
 */

#include <cstdio>
#include <map>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::map<long, long> m;
    bool reached(false);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++m[x];
      if (m[x] >= k) {
        reached = true;
      }
    }

    printf("%ld\n", reached ? (k - 1) : n);
  }
}
