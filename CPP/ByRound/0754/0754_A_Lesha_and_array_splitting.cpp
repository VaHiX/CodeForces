/*
 * Problem URL : https://codeforces.com/problemset/problem/754/A
 * Submit Date : 2025-08-16
 */

#include <bits\stdc++.h>
int main() {
  int n, m, s = 0, f = 0, a;
  std::cin >> n, m = n;
  for (; m--;) {
    std::cin >> a;
    s += a;
    if (a)
      f = n - m - 1;
  }
  if (s)
    printf("YES\n1\n1 %d", n);
  else if (f > 0)
    printf("YES\n2\n1 %d\n%d %d", f, f + 1, n);
  else
    printf("NO");
}
