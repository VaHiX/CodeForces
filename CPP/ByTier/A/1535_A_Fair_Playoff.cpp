/*
 * Problem URL : https://codeforces.com/problemset/problem/1535/A
 * Submit Date : 2025-08-23
 */

#include <algorithm>
#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<std::pair<long, long>> a(4);
    for (long p = 0; p < 4; p++) {
      scanf("%ld", &a[p].first);
      a[p].second = p;
    }
    sort(a.rbegin(), a.rend());
    long x(a[0].second), y(a[1].second);
    x /= 2;
    y /= 2;
    puts(x == y ? "NO" : "YES");
  }
}