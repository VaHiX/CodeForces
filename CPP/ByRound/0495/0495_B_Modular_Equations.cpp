/*
 * Problem URL : https://codeforces.com/contest/495/problem/B
 * Submit Date : 2025-09-05
 */

#include <ios>
int a, b, c;
main() {
  scanf("%d%d", &a, &b), a -= b;
  if (!a)
    printf("infinity");
  else {
    for (int i = 1; i * i <= a; ++i)
      if (!(a % i)) {
        if (i > b)
          ++c;
        if (a / i > b && a / i != i)
          ++c;
      }
    printf("%d", c);
  }
}