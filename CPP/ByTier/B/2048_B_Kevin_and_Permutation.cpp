/*
 * Problem URL : https://codeforces.com/problemset/problem/2048/B
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(n + 1);
    long cur(1);
    for (long p = 1; k * p <= n; p++) {
      v[p * k] = cur++;
    }
    for (long p = 1; p <= n; p++) {
      if (!v[p]) {
        v[p] = cur++;
      }
      printf("%ld ", v[p]);
    }
    puts("");
  }
}
