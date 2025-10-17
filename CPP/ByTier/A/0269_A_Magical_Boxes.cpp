/*
 * Problem URL : https://codeforces.com/contest/269/problem/A
 * Submit Date : 2025-09-06
 */

#include <cstdio>

int main() {

  long n;
  scanf("%ld\n", &n);

  int maxp = 0;
  while (n--) {
    int k, a;
    scanf("%d %d", &k, &a);
    int m(0), t(1);
    while (t < a) {
      t *= 4;
      ++m;
    }
    if (maxp < k + m) {
      maxp = k + m;
    }
    if (maxp == k) {
      ++maxp;
    }
  }

  printf("%d\n", maxp);

  return 0;
}
