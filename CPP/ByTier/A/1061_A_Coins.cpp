/*
 * Problem URL : https://codeforces.com/contest/1061/problem/A
 * Submit Date : 2025-08-30
 */

/*
 * Problem URL : https://codeforces.com/contest/1061/problem/A
 * Submit Date : 2025-08-28
 */

#include <cstdio>

int main() {

  long n, s;
  scanf("%ld %ld", &n, &s);
  long cnt = (s + n - 1) / n;
  printf("%ld\n", cnt);

  return 0;
}
