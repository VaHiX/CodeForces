/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>
#include <iostream>

int main() {
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  printf("%d\n", std::min(n - a, b + 1));
  return 0;
}
