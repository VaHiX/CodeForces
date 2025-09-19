/*
 * Problem URL : https://codeforces.com/problemset/problem/2115/A
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int t, n, a[N], dp[N], _gcd[N][N];
void min(int &x, int y) {
  if (x > y)
    x = y;
}
int main() {
  for (int i = 0; i <= 5000; i++)
    _gcd[i][0] = _gcd[0][i] = _gcd[i][i] = i;
  for (int i = 1; i <= 5000; i++)
    for (int j = 1; j < i; j++) {
      _gcd[i][j] = _gcd[j][i] = _gcd[j][i % j];
    }
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int d = 0, p = 0, cnt = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", &a[i]), d = _gcd[d][a[i]], p = max(p, a[i]);
    for (int i = 1; i <= n; i++)
      cnt += (a[i] == d);
    if (cnt) {
      printf("%d\n", n - cnt);
      continue;
    }
    for (int i = 1; i <= p; i++)
      dp[i] = n + 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= p; j++)
        min(dp[_gcd[j][a[i]]], dp[j] + 1);
      dp[a[i]] = 0;
    }
    printf("%d\n", dp[d] + n - 1);
  }
  return 0;
}
