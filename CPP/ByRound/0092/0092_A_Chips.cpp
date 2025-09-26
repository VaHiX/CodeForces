/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  m %= (n * (n + 1) / 2);
  int x = (sqrt(8 * m + 1) - 1) / 2.0;
  printf("%d\n", m - x * (x + 1) / 2);
  return 0;
}
