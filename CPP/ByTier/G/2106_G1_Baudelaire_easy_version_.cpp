/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/G1
 * Submit Date : 2025-08-17
 */

#include <cstdio>
int ans[1005];
int main() {
  int t, n, u, v, p;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
      scanf("%d%d", &u, &v);
    printf("? 1 1 1\n");
    fflush(stdout);
    scanf("%d", &ans[1]);
    if (ans[1] & 1) {
      for (int i = 2; i <= n; i++) {
        printf("? 1 1 %d\n", i);
        fflush(stdout);
        scanf("%d", &ans[i]);
        ans[i] -= ans[1];
      }
    } else {
      if (ans[1]) {
        printf("? 2 1\n");
        fflush(stdout);
      }
      for (int i = 2; i <= n; i++) {
        printf("? 1 1 %d\n", i);
        fflush(stdout);
        scanf("%d", &ans[i]);
      }
      printf("? 2 1\n");
      fflush(stdout);
      printf("? 1 1 1\n");
      fflush(stdout);
      scanf("%d", &ans[1]);
      ans[1] /= 2;
    }
    printf("!");
    for (int i = 1; i <= n; i++)
      printf(" %d", ans[i]);
    printf("\n");
    fflush(stdout);
  }
  return 0;
}
