/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/E
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int tot, he[N], ne[N * 2], to[N * 2];
long long siz[N], s[N], ans, de[N];
void dfs(int x, int fa) {
  int i, y;
  siz[x] = 0;
  s[x] = 0;
  for (i = he[x]; i != 0; i = ne[i]) {
    y = to[i];
    if (y != fa) {
      de[y] = de[x] + 1;
      dfs(y, x);
      ans += s[x] * siz[y] + siz[x] * (siz[y] + s[y]) - siz[x] * siz[y];
      siz[x] += siz[y];
      s[x] += s[y] + siz[y];
    }
  }
  siz[x]++;
}
int main() {
  int T, n, i, x, y;
  long long sum;
  scanf("%d", &T);
  while (T > 0) {
    T--;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
      he[i] = 0;
    tot = 0;
    ans = 0;
    for (i = 1; i < n; i++) {
      scanf("%d%d", &x, &y);
      tot++;
      ne[tot] = he[x];
      to[tot] = y;
      he[x] = tot;
      tot++;
      ne[tot] = he[y];
      to[tot] = x;
      he[y] = tot;
    }
    de[1] = 0;
    dfs(1, 0);
    for (i = 0; i <= n; i++)
      s[i] = 0;
    for (i = 1; i <= n; i++) {
      ans += de[i] * (de[i] + 1) / 2;
      s[de[i]]++;
    }
    sum = 0;
    for (i = 1; i <= n; i++) {
      ans = ans - (s[i - 1] * i - sum) * s[i];
      sum += s[i] * i;
      s[i] += s[i - 1];
    }
    printf("%lld\n", ans);
  }
  return 0;
}