/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    long long n;
    scanf("%I64d", &n);
    if ((n + 1) % 4 == 0) {
      printf("%I64d\n", n + 1);
    } else if ((n + 1) % 2 == 0) {
      printf("%I64d\n", n * 2 + 1);
    } else {
      printf("%I64d\n", n * 4 + 1);
    }
  }
  return 0;
}
