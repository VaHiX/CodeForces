/*
 * Problem URL : https://codeforces.com/problemset/problem/821/C
 * Submit Date : 2025-08-19
 */

#include <stdio.h>
int main() {
  char op[10];
  int n, count = 0;
  int s[300005];
  scanf("%d", &n);
  int top = 0, j = 1;
  for (int i = 0; i < 2 * n; i++) {
    scanf("%s", op);
    if (op[0] == 'a') {
      scanf("%d", &s[++top]);
    } else {
      if (top) {
        if (s[top] == j)
          top--;
        else {
          top = 0;
          count++;
        }
      }
      j++;
    }
  }
  printf("%d", count);
}
