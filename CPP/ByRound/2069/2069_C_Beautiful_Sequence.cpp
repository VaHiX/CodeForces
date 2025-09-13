/*
 * Problem URL : https://codeforces.com/problemset/problem/2069/C
 * Submit Date : 2025-08-23
 */

#include <stdio.h>
#define M 998244353

int main() {
  int T, n, i;
  char s[2], x;
  unsigned int A, B, C;

  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (i = 0, A = B = C = 0; i < n; i++) {
      scanf("%s", s);
      x = s[0];
      if (x == 50)
        B = ((B << 1) + A) % M;
      else if (x == 49)
        A++;
      else
        C = (C + B) % M;
    }
    printf("%u\n", C);
  }

  return 0;
}