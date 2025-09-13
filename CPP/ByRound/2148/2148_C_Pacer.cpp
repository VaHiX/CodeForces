/*
 * Problem URL : https://codeforces.com/contest/2148/problem/C
 * Submit Date : 2025-09-13
 */

#include <stdio.h>
#include <stdlib.h>

int a[200005], b[200005];

int main() {
  int N, M, i, j, k, T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; i++)
      scanf("%d %d", &a[i], &b[i]);
    a[0] = 0;
    b[0] = 0;
    for (i = 1; i <= N; i++)
      if (((a[i] - a[i - 1]) - (b[i] - b[i - 1])) % 2)
        M--;
    printf("%d\n", M);
  }
}