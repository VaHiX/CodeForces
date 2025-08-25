/*
 * Problem URL : https://codeforces.com/problemset/problem/2065/C1
 * Submit Date : 2025-08-10
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> a(n);
    for (size_t p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long b;
    scanf("%ld", &b);

    bool res(true);
    a[0] = std::min(a[0], b - a[0]);
    for (size_t p = 1; res && p < n; p++) {
      if (a[p - 1] <= a[p] && a[p - 1] <= b - a[p]) {
        a[p] = std::min(a[p], b - a[p]);
      } else if (a[p - 1] <= a[p]) {
      } else if (a[p - 1] <= b - a[p]) {
        a[p] = b - a[p];
      } else {
        res = false;
      }
    }

    puts(res ? "YES" : "NO");
  }
}
