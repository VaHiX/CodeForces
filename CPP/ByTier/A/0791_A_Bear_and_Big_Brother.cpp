/*
 * Problem URL : https://codeforces.com/contest/791/problem/A
 * Submit Date : 2025-09-01
 */

#include <cstdio>

int main() {

  const int A = 3;
  const int B = 2;

  int a, b;
  scanf("%d %d", &a, &b);
  int n(0);
  while (a <= b) {
    a *= A;
    b *= B;
    ++n;
  }
  printf("%d\n", n);

  return 0;
}
