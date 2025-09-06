/*
 * Problem URL : https://codeforces.com/contest/914/problem/A
 * Submit Date : 2025-08-31
 */



#include <cmath>
#include <cstdio>

int main() {

  long n;
  scanf("%ld", &n);
  long ans(-1e8);
  while (n--) {
    long x;
    scanf("%ld", &x);
    if (x >= 0) {
      long s = sqrt(x);
      if ((s * s < x) && (x > ans)) {
        ans = x;
      }
    } else {
      ans = (ans > x) ? ans : x;
    }
  }

  printf("%ld\n", ans);

  return 0;
}
