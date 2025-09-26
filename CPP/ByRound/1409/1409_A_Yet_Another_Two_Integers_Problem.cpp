/*
 * Problem URL : https://codeforces.com/contest/1409/problem/A
 * Submit Date : 2025-08-24
 */

/*
 * Problem URL : https://codeforces.com/problemset/problem/1409/A
 * Submit Date : 2025-08-23
 */

#include <cstdio>

int main() {

  const long N = 10;
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    long diff = a - b;
    if (diff < 0) {
      diff = -diff;
    }
    long ans = (diff + N - 1) / N;
    printf("%ld\n", ans);
  }

  return 0;
}
