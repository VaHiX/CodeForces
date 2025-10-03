/*
 * Problem URL : https://codeforces.com/problemset/problem/1512/A
 * Submit Date : 2025-08-23
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
    std::vector<std::pair<long, long>> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);
      v[p].second = p + 1;
    }
    sort(v.begin(), v.end());
    long res = (v[0].first == v[1].first) ? v.back().second : v[0].second;
    printf("%ld\n", res);
  }
}
