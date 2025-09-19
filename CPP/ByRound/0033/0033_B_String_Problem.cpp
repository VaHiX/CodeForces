/*
 * Problem URL : https://codeforces.com/problemset/problem/33/B
 * Submit Date : 2025-08-16
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 30;
const int inf = 1e9;
char s1[100010], s2[100010], a, b, s[100010];
int l, n, w, f[maxn][maxn], minn;
typedef long long ll;
ll ans;
int main() {
  scanf("%s%s%d", s1, s2, &n);
  l = strlen(s1);
  if (l != strlen(s2)) {
    printf("-1\n");
    return 0;
  }
  for (int i = 0; i < 26; i++)
    for (int j = 0; j < 26; j++)
      if (i != j)
        f[i][j] = inf;
  while (n--) {
    scanf(" %c %c%d", &a, &b, &w);
    f[a - 'a'][b - 'a'] = min(f[a - 'a'][b - 'a'], w);
  }
  for (int k = 0; k < 26; k++)
    for (int i = 0; i < 26; i++)
      for (int j = 0; j < 26; j++)
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
  for (int i = 0; i < l; i++) {
    minn = inf;
    for (int j = 0; j < 26; j++)
      if (minn > f[s1[i] - 'a'][j] + f[s2[i] - 'a'][j])
        minn = f[s1[i] - 'a'][j] + f[s2[i] - 'a'][j], s[i] = j + 'a';
    if (minn == inf) {
      printf("-1\n");
      return 0;
    }
    ans += minn;
  }
  printf("%d\n", ans);
  printf("%s\n", s);
  return 0;
}