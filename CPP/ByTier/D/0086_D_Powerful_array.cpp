/*
 * Problem URL : https://codeforces.com/problemset/problem/86/D
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int i, l, r, n, m, b, c[200005], f[1000005];
long long cnt, ans[200005];
struct Q {
  int l, r, k;
  bool operator<(const Q &a) const {
    return (l / b < a.l / b) || (l / b == a.l / b && r < a.r);
  }
} a[200005];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> m;
  for (i = 0; i < n; i++)
    cin >> c[i];
  for (i = 0; i < m; i++) {
    cin >> a[i].l >> a[i].r;
    a[i].l--, a[i].r--;
    a[i].k = i;
  }
  b = sqrt(n);
  sort(a, a + m);
  r = -1;
  for (i = 0; i < m; i++) {
    for (; l < a[i].l; cnt -= 1ll * c[l] * (2 * --f[c[l++]] + 1))
      ;
    for (; l > a[i].l; cnt += 1ll * c[--l] * (2 * f[c[l]]++ + 1))
      ;
    for (; r < a[i].r; cnt += 1ll * c[++r] * (2 * f[c[r]]++ + 1))
      ;
    for (; r > a[i].r; cnt -= 1ll * c[r] * (2 * --f[c[r--]] + 1))
      ;
    ans[a[i].k] = cnt;
  }
  for (i = 0; i < m; i++)
    cout << ans[i] << "\n";
}
