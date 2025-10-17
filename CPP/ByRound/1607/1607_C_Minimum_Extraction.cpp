/*
 * Problem URL : https://codeforces.com/contest/1607/problem/C
 * Submit Date : 2025-08-28
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
    sort(a.begin(), a.end());
    long res(a[0]);
    for (long p = 1; p < a.size(); p++) {
      long diff = a[p] - a[p - 1];
      res = (res > diff) ? res : diff;
    }

    printf("%ld\n", res);
  }
}
