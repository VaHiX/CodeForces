/*
 * Problem URL : https://codeforces.com/problemset/problem/1445/A
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    bool res(true);
    for (long p = 0; p < n; p++) {
      if (a[p] + b[p] > x) {
        res = false;
        break;
      }
    }
    puts(res ? "Yes" : "No");
  }

  return 0;
}
