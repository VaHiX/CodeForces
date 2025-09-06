/*
 * Problem URL : https://codeforces.com/problemset/problem/1987/C
 * Submit Date : 2025-08-12
 */

#include <cstdio>
#include <vector>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> h(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &h[p]);
    }
    long cnt(h.back());
    for (long p = n - 2; p >= 0; p--) {
      long tmp = cnt + 1;
      cnt = (tmp > h[p] ? tmp : h[p]);
    }

    printf("%ld\n", cnt);
  }
}
