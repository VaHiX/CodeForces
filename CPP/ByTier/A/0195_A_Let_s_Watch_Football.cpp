/*
 * Problem URL : https://codeforces.com/problemset/problem/195/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {

  int a(0), b(0), c(0);
  scanf("%d %d %d", &a, &b, &c);
  int waitingTime = ceil((1.0 * a / b) * c - c);
  printf("%d\n", waitingTime);
  return 0;
}
