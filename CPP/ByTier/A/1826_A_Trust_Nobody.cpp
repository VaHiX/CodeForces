/*
 * Problem URL : https://codeforces.com/problemset/problem/1826/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int t;
int n, cnt[110];
int main() {
  for (cin >> t; t--;) {
    cin >> n;
    fill(cnt, cnt + n + 1, 0);
    for (int i = 1, x; i <= n; i++)
      scanf("%d", &x), cnt[x]++;
    int ans = -1;
    for (int i = 0, s = 0; i <= n; i++) {
      s += cnt[i];
      if (i == n - s)
        ans = i;
    }
    printf("%d\n", ans);
  }
  return 0;
}