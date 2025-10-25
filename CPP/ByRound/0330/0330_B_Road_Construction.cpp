/*
 * Problem URL : https://codeforces.com/problemset/problem/330/B
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {
  int n, m, a, b;
  bool fire[1001] = {false};
  scanf("%d%d", &n, &m);
  while (m--) {
    scanf("%d%d", &a, &b);
    fire[a] = true;
    fire[b] = true;
  }
  int x = 1;
  while (fire[x]) {
    x++;
  }
  printf("%d\n", n - 1);
  for (int i = 1; i < x; ++i) {
    printf("%d %d\n", i, x);
  }
  for (int i = x + 1; i <= n; ++i) {
    printf("%d %d\n", x, i);
  }
  return 0;
}
