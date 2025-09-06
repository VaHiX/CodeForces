/*
 * Problem URL : https://codeforces.com/contest/1465/problem/C
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define LL long long
#define N 100005
using namespace std;
int fa[N];
int gf(int k) {
  if (fa[k] == k)
    return k;
  fa[k] = gf(fa[k]);
  return fa[k];
}
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
      fa[i] = i;

    int ans = 0;
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      if (x != y) {
        ans++;
        if (fa[x] == gf(y))
          ans++;
        fa[x] = fa[y];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
