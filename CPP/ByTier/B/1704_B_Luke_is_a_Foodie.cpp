/*
 * Problem URL : https://codeforces.com/problemset/problem/1704/B
 * Submit Date : 2025-08-22
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1704/B
 * Submit Date : 2025-08-21
 */

#include <cstdio>

int main() {

  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    long cnt(0), low(0), high(2e9 + 7);
    for (long p = 0; p < n; p++) {
      long cur;
      scanf("%ld", &cur);
      long left = cur - x;
      long right = cur + x;
      low = (low > left) ? low : left;
      high = (high < right) ? high : right;
      if (low > high) {
        ++cnt;
        low = left;
        high = right;
      }
    }

    printf("%ld\n", cnt);
  }
}
