/*
 * Problem URL : https://codeforces.com/contest/579/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/579/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  const int N = 2;

  long x;
  scanf("%ld\n", &x);

  int ans(0);
  while (x > 0) {
    ans += x % N;
    x /= N;
  }
  printf("%d\n", ans);

  return 0;
}
