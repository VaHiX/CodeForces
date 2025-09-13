/*
 * Problem URL : https://codeforces.com/problemset/problem/1684/D
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
typedef long long ll;
const int N = 2e5 + 3;
int n, m, a[N];
ll ans;
int main() {
  int T;
  scanf("%d", &T);
  for (; T--;) {
    scanf("%d%d", &n, &m);
    ans = 0;
    for (int i = 1; i <= n; i++)
      scanf("%d", a + i), ans += a[i], a[i] += i;
    std::sort(a + 1, a + 1 + n,
              [](const int &a, const int &b) { return a > b; });
    for (int i = 1; i <= m; i++)
      ans += i + n - m - a[i];
    printf("%lld\n", ans);
  }
  return 0;
}