/*
 * Problem URL : https://codeforces.com/contest/705/problem/A
 * Submit Date : 2025-09-02
 */



#include <cstdio>

int main() {

  int n;
  scanf("%d\n", &n);
  for (int p = 0; p < n; p++) {
    printf((p % 2) ? "I love " : "I hate ");
    printf((p == n - 1) ? "it" : "that ");
  }

  return 0;
}
