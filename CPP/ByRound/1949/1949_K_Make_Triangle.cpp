/*
 * Problem URL : https://codeforces.com/contest/1949/problem/K
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int N = 222222;
int n, a[3], f[N];
LL s[N], m, t[3];
vector<int> v[3];
int main() {
  int T, i, j, x, y;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (j = 0; j < 3; j++)
      scanf("%d", a + j);
    for (i = 1; i <= n; i++)
      scanf("%d", f + i);
    sort(f + 1, f + n + 1);
    for (i = 1; i <= n; i++)
      s[i] = s[i - 1] + f[i];
    m = (s[n] - 1) / 2;
    for (j = 0; j < 3; j++)
      t[j] = 0, v[j].clear();
    y = 1;
    for (i = n; i >= 1; i--) {
      x = 1;
      for (j = 0; j < 3; j++)
        if (a[j] && t[j] + f[i] + s[a[j] - 1] <= m) {
          v[j].push_back(f[i]);
          a[j]--;
          t[j] += f[i];
          x = 0;
          break;
        }
      if (x) {
        printf("NO\n");
        y = 0;
        break;
      }
    }
    if (y) {
      printf("YES\n");
      for (j = 0; j < 3; j++) {
        for (i = 0; i < v[j].size(); i++)
          printf("%d ", v[j][i]);
        printf("\n");
      }
    }
  }
  return 0;
}