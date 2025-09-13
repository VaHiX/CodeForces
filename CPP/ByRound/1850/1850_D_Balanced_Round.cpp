/*
 * Problem URL : https://codeforces.com/problemset/problem/1850/D
 * Submit Date : 2025-08-18
 */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());

    long cur(1), mx(1);
    for (long p = 1; p < n; p++) {
      if (a[p] <= a[p - 1] + k) {
        ++cur;
        mx = (mx > cur ? mx : cur);
      } else {
        cur = 1;
      }
    }

    printf("%ld\n", n - mx);
  }
}
