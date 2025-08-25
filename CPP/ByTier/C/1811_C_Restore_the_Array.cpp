/*
 * Problem URL : https://codeforces.com/problemset/problem/1811/C
 * Submit Date : 2025-08-19
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> b(n - 1);
    for (long p = 0; p < n - 1; p++) {
      scanf("%ld", &b[p]);
    }
    printf("%ld ", b[0]);
    for (long p = 1; p < n - 1; p++) {
      printf("%ld ", b[p - 1] < b[p] ? b[p - 1] : b[p]);
    }
    printf("%ld\n", b.back());
  }
}
