/*
 * Problem URL : https://codeforces.com/contest/1464/problem/A
 * Submit Date : 2025-09-01
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define maxn 100005
using namespace std;

int T, n, m, i, j, k, fa[maxn], a[maxn][2];
int find(int x) { return (fa[x] == x) ? x : fa[x] = find(fa[x]); }

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
      fa[i] = i;
    int ans = m;
    for (i = 1; i <= m; i++) {
      scanf("%d%d", &j, &k);
      if (j == k)
        ans--;
      else if (find(j) == find(k))
        ans++;
      else
        fa[find(j)] = find(k);
    }
    printf("%d\n", ans);
  }
}
