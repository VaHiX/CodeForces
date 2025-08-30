/*
 * Problem URL : https://codeforces.com/problemset/problem/2041/A
 * Submit Date : 2025-08-10
 */

#include <cstdio>

int main() {

  bool v[6] = {0};
  for (int p = 0; p < 4; p++) {
    int x;
    scanf("%d", &x);
    v[x] = 1;
  }

  for (int p = 1; p <= 5; p++) {
    if (!v[p]) {
      printf("%d\n", p);
      break;
    }
  }

  return 0;
}
