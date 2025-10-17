/*
 * Problem URL : https://codeforces.com/problemset/problem/808/E
 * Submit Date : 2025-08-18
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
struct Node {
  long long x, y;
  bool operator<(const Node &a) const { return y * a.x > x * a.y; }
} a[N];
int n, m, maxx;
long long ans, f[N * 3];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%lld%lld", &a[i].x, &a[i].y);
  std::sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    for (int j = std::min(maxx + 3, m); j >= std::max(maxx - 3, (int)a[i].x);
         j--)
      f[j] = max(f[j - a[i].x] + a[i].y, f[j]);
    if (maxx < m)
      maxx += a[i].x;
  }
  for (int i = 1; i <= m; i++)
    ans = std::max(ans, f[i]);
  printf("%lld\n", ans);
  return 0;
}