/*
 * Problem URL : https://codeforces.com/problemset/problem/1279/C
 * Submit Date : 2025-08-20
 */

#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int KK[100000];
    int n, m, h, i;
    long long ans;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      KK[a - 1] = i;
    }
    ans = m;
    i = -1;
    for (h = 0; h < m; h++) {
      int a;
      scanf("%d", &a);
      if (i < KK[a - 1]) {
        i = KK[a - 1];
        ans += (i - h) * 2;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
