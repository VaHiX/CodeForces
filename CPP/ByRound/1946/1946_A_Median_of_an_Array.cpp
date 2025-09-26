/*
 * Problem URL : https://codeforces.com/problemset/problem/1946/A
 * Submit Date : 2025-08-12
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
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    sort(v.begin(), v.end());
    long idx = (n - 1) / 2;

    long cnt(0);
    for (long p = idx; p < n && v[p] == v[idx]; p++, cnt++)
      ;
    printf("%ld\n", cnt);
  }
}
