/*
 * Problem URL : https://codeforces.com/contest/2032/problem/D
 * Submit Date : 2025-09-09
 */

#include <bits/stdc++.h>
using namespace std;
int a[1000010], p[1000010];
signed main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int l = n - 2, r = n - 1, o;
    for (int i = 1; i <= n; i++)
      p[i] = 0;
    while (l) {
      printf("? %d %d\n", l, r);
      fflush(stdout);
      scanf("%d", &o);
      if (o == 0)
        p[r] = l, r--;
      l--;
    }
    printf("! ");
    for (int i = 1; i <= n - 1; i++)
      printf("%d ", p[i]);
    printf("\n");
    fflush(stdout);
  }
}