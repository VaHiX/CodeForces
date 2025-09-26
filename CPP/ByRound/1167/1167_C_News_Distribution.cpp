/*
 * Problem URL : https://codeforces.com/contest/1167/problem/C
 * Submit Date : 2025-08-29
 */

/*
 * Problem URL : https://codeforces.com/contest/1167/problem/C
 * Submit Date : 2025-08-28
 */

#include <cstdio>
const int N = 5e5 + 50;
int n, m, k, x, y, fa[N], siz[N];
int fd(int u) { return fa[u] = (fa[u] == u ? u : fd(fa[u])); }
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &k);
    if (k) {
      scanf("%d", &x);
      x = fd(x);
      for (int j = 1; j < k; j++) {
        scanf("%d", &y);
        y = fd(y);
        fa[y] = x;
      }
    }
  }
  for (int i = 1; i <= n; i++)
    siz[fd(i)]++;
  for (int i = 1; i <= n; i++)
    printf("%d ", siz[fa[i]]);
  return 0;
}