/*
 * Problem URL : https://codeforces.com/problemset/problem/1824/A
 * Submit Date : 2025-08-21
 */

#include <bits/stdc++.h>
using namespace std;
int x[100010];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, m, L = 0, R = 0, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", &x[i]);
      if (x[i] == -1)
        L++, i--, n--;
      else if (x[i] == -2)
        R++, i--, n--;
    }
    sort(x + 1, x + n + 1);
    n = unique(x + 1, x + n + 1) - x - 1;
    ans = max(n + min(m - n, R), n + min(m - n, L));
    for (int i = 1; i <= n; i++)
      ans = max(ans, n + min(x[i] - i, L) + min(m - x[i] - (n - i), R));
    printf("%d\n", ans);
  }
  return 0;
}
