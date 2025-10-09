/*
 * Problem URL : https://codeforces.com/problemset/problem/1092/D1
 * Submit Date : 2025-08-13
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int n, wa[200005], sta[200005], top;
int main() {
  scanf("%d", &n);
  top = 0;
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    if (!top || abs(sta[top] - k) & 1)
      sta[++top] = k;
    else
      top--;
  }
  if (top > 1)
    printf("NO");
  else
    printf("YES");
  return 0;
}