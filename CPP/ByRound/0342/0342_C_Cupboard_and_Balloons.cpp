/*
 * Problem URL : https://codeforces.com/contest/342/problem/C
 * Submit Date : 2025-09-09
 */

/*
 * Problem URL : https://codeforces.com/contest/342/problem/C
 * Submit Date : 2025-09-08
 */

#include <cstdio>

int main() {

  const double x = 0.8660254;

  long r, h;
  scanf("%ld %ld\n", &r, &h);
  long s = (h + r / 2) / r;
  h = h + r - r * s;
  s *= 2;
  if (r * x <= h) {
    ++s;
  }
  printf("%ld\n", s);
  return 0;
}
