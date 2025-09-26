/*
 * Problem URL : https://codeforces.com/contest/1521/problem/B
 * Submit Date : 2025-08-28
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    printf("%ld\n", n / 2);
    for (long p = 1; p < n; p += 2) {
      printf("%ld %ld %ld 1000000007\n", p, p + 1,
             a[p - 1] < a[p] ? a[p - 1] : a[p]);
    }
  }
}
