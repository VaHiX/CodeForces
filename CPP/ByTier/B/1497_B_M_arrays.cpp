/*
 * Problem URL : https://codeforces.com/contest/1497/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v(m, 0);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      ++v[x % m];
    }
    long cnt(v[0] > 0);
    for (long p = 1; p <= m - p; p++) {
      if (p == m - p && v[p] > 0) {
        ++cnt;
      } else if (v[p] || v[m - p]) {
        ++cnt;
        long rem = v[p] - v[m - p];
        if (rem < 0) {
          rem *= -1;
        }
        if (rem > 1) {
          cnt += rem - 1;
        }
      }
    }

    printf("%ld\n", cnt);
  }
}
