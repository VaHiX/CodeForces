/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/C
 * Submit Date : 2025-08-10
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);

    std::vector<long> a(n), b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }

    long left(0), right(2 * k);
    for (long p = 0; p < n; p++) {
      long curleft = a[p] + (b[p] < 0 ? 0 : b[p]);
      left = (left > curleft ? left : curleft);

      long curright = a[p] + (b[p] < 0 ? k : b[p]);
      right = (right < curright ? right : curright);
    }

    long ans(left <= right ? (right - left + 1) : 0);
    printf("%ld\n", ans);
  }
}
