/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cmath>
#include <cstdio>

int main() {

  int n(0);
  scanf("%d", &n);
  int temp = sqrt(1 + 8 * n);
  if (temp * temp == 1 + 8 * n) {
    puts("YES");
  } else {
    puts("NO");
  }

  return 0;
}
