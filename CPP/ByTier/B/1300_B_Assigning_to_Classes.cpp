/*
 * Problem URL : https://codeforces.com/contest/1300/problem/B
 * Submit Date : 2025-09-11
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
    std::vector<long> a(2 * n);
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());
    printf("%ld\n", a[n] - a[n - 1]);
  }

  return 0;
}
