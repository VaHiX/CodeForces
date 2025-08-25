/*
 * Problem URL : https://codeforces.com/problemset/problem/1867/A
 * Submit Date : 2025-08-15
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
    std::vector<std::pair<long, long>> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p].first);
      a[p].second = p;
    }
    sort(a.rbegin(), a.rend());
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      b[a[p].second] = p + 1;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", b[p]);
    }
    puts("");
  }
}
