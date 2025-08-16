/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>
#include <iostream>

int main() {
  int n, k, l, c, d, p, nl, np;
  scanf("%d %d %d %d %d %d %d %d", &n, &k, &l, &c, &d, &p, &nl, &np);
  printf("%d\n",
         std::min(p / (n * np), std::min((k * l) / (n * nl), (c * d) / n)));
  return 0;
}
