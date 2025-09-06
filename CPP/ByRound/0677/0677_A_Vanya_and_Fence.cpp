/*
 * Problem URL : https://codeforces.com/contest/677/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  int n, h;
  scanf("%d %d", &n, &h);
  int width(n);
  while (n--) {
    int x;
    scanf("%d ", &x);
    width += (x > h);
  }

  printf("%d\n", width);

  return 0;
}
