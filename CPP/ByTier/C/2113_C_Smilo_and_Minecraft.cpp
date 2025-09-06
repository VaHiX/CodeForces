/*
 * Problem URL : https://codeforces.com/problemset/problem/2113/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 500 + 1;
int n, m, k;
char s[N][N];
int cnt[N][N];
int getg(int x, int y) {
  int l = max(y - k, 1), u = max(x - k, 1);
  int r = min(y + k, m), d = min(x + k, n);
  return cnt[d][r] - cnt[d][l - 1] - cnt[u - 1][r] + cnt[u - 1][l - 1];
}
void work() {
  scanf("%d%d%d", &n, &m, &k);
  k--;
  for (int i = 1; i <= n; i++)
    scanf("%s", s[i] + 1);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cnt[i][j] =
          cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1] + (s[i][j] == 'g');
  int tot = cnt[n][m], ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (s[i][j] == '.')
        ans = max(ans, tot - getg(i, j));
  printf("%d\n", ans);
  return;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    work();
  return 0;
}