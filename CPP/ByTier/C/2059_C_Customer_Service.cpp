/*
 * Problem URL : https://codeforces.com/problemset/problem/2059/C
 * Submit Date : 2025-08-24
 */

#include <algorithm>
#include <stdio.h>
using namespace std;

int n, a[303][303], t[303];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      scanf("%d", &a[i][j]);
  for (int i = 1; i <= n; i++)
    for (int j = n; j >= 0; j--)
      if (a[i][j] != 1) {
        t[i] = n - j;
        break;
      }
  sort(t + 1, t + n + 1);
  int ans = 1;
  for (int i = 1; i <= n; i++)
    if (t[i] >= ans)
      ans++;
  printf("%d\n", min(ans, n));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    solve();
}