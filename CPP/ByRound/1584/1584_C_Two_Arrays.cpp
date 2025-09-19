/*
 * Problem URL : https://codeforces.com/contest/1584/problem/C
 * Submit Date : 2025-09-08
 */

#include <algorithm>
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
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    bool res(true);
    for (long p = 0; p < n; p++) {
      if (b[p] < a[p] || b[p] > a[p] + 1) {
        res = false;
        break;
      }
    }
    puts(res ? "YES" : "NO");
  }
}
