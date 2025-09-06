/*
 * Problem URL : https://codeforces.com/contest/851/problem/A
 * Submit Date : 2025-08-31
 */

/*
 * Problem URL : https://codeforces.com/contest/851/problem/A
 * Submit Date : 2025-08-31
 */



#include <cstdio>

int main() {

  long n, k, t;
  scanf("%ld %ld %ld\n", &n, &k, &t);
  long ans(0);
  if (t <= k) {
    ans = t;
  } else if (t <= n) {
    ans = k;
  } else if (t <= n + k) {
    ans = n + k - t;
  }

  ans = (ans < n) ? ans : n;
  printf("%ld\n", ans);

  return 0;
}
