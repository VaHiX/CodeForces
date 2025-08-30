/*
 * Problem URL : https://codeforces.com/problemset/problem/2123/C
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
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }

    std::vector<int> b(n, 0);

    long x(1e7);
    for (long p = 0; p < n; p++) {
      if (a[p] < x) {
        b[p] = 1;
        x = a[p];
      }
    }
    x = 0;
    for (long p = n - 1; p >= 0; p--) {
      if (a[p] > x) {
        b[p] = 1;
        x = a[p];
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%d", b[p]);
    }
    puts("");
  }
}
