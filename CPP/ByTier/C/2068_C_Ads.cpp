/*
 * Problem URL : https://codeforces.com/problemset/problem/2068/C
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
const int N = 1e6 + 5;
int n, t, a[N];
bool vis[N];
void solve() {
  std::cin >> n >> t;
  for (int i = 1; i <= n; i++)
    std::cin >> a[i];
  int ans = 0;
  std::sort(a + 1, a + n + 1), memset(vis + 1, false, sizeof(bool) * n);
  for (int i = 1, j = n, k = n; i <= n; i++, j--)
    if (!vis[i]) {
      for (; i < j && (a[i] + a[j] >= t || vis[j]); j--)
        ;
      vis[i] = true, ans++;
      if (i < j && !vis[j] && a[i] + a[j] < t)
        vis[j] = true;
      if (a[i] < t) {
        for (; i < k && vis[k]; k--)
          ;
        if (i < k && !vis[k])
          vis[k] = true;
      }
    }
  std::cout << ans - 1 << "\n";
}
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr),
      std::cout.tie(nullptr);
  int T;
  std::cin >> T;
  for (; T--;)
    solve();
  return 0;
}
