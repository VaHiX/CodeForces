/*
 * Problem URL : https://codeforces.com/contest/652/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {
  int h1, h2, a, b;
  scanf("%d %d\n%d %d", &h1, &h2, &a, &b);

  h2 -= h1 + 8 * a;
  a = (a - b) * 12;

  if (h2 <= 0) {
    puts("0");
  } else if (a <= 0) {
    puts("-1");
  } else {
    printf("%d\n", (h2 + a - 1) / a);
  }

  return 0;
}
