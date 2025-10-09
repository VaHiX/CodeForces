/*
 * Problem URL : https://codeforces.com/contest/527/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/527/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>

int main() {

  long long a, b;
  scanf("%lld %lld\n", &a, &b);
  long long ans(0);
  while (a > 0 && b > 0) {
    if (a > b) {
      ans += a / b;
      a %= b;
    } else {
      ans += b / a;
      b %= a;
    }
  }

  printf("%lld\n", ans);

  return 0;
}
