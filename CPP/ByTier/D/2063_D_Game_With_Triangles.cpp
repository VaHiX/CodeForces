/*
 * Problem URL : https://codeforces.com/problemset/problem/2063/D
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, a[N], b[N];
ll sa[N], sb[N];
ll calc(int x, int k) { return sa[x] + sb[k - x]; }
void clr() {}
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++)
    cin >> b[i];
  sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
  int na = 0, nb = 0, kmax = 0;
  while (2 * (na + 1) <= n - nb && 2 * nb < m - na ||
         2 * (nb + 1) <= m - na && 2 * na < n - nb) {
    if (n - nb - 2 * na >= m - na - 2 * nb)
      kmax++, na++;
    else
      kmax++, nb++;
  }
  cout << kmax << '\n';
  for (int i = 1; i <= n / 2; i++)
    sa[i] = sa[i - 1] + a[n - i + 1] - a[i];
  for (int i = 1; i <= m / 2; i++)
    sb[i] = sb[i - 1] + b[m - i + 1] - b[i];
  for (int k = 1; k <= kmax; k++) {
    const int LL = k - min({k, m / 2, n, m - k}),
              RR = min({k, n / 2, m, n - k});
    // n-2*x>=(k-x)    n-k>=x
    int L = LL, R = RR + 1, mid;
    while (L < R - 1) {
      mid = L + R >> 1;
      if (calc(mid, k) >= calc(mid - 1, k))
        L = mid;
      else
        R = mid;
    }
    cout << calc(L, k) << ' ';
  }
  cout << '\n';
  clr();
}
int main() {
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}