/*
 * Problem URL : https://codeforces.com/problemset/problem/2066/C
 * Submit Date : 2025-08-23
 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5;
const ll P = 1e9 + 7;
int T, n, a[N], c[N], d[N];
ll ans, f[N];
void solve() {
  ans = 0, f[0] = 1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i] ^= a[i - 1], c[i] = a[i];
  }
  sort(c + 1, c + 1 + n);
  int m = unique(c + 1, c + 1 + n) - c - 1;
  for (int i = 1; i <= n; i++)
    d[i] = lower_bound(c, c + m + 1, a[i]) - c;
  for (int i = 1; i <= n; i++)
    f[d[i - 1]] = (3 * f[d[i - 1]] + 2 * f[d[i]]) % P;
  for (int i = 0; i <= n; i++)
    ans = (ans + f[d[i]]) % P, f[d[i]] = 0;
  printf("%lld\n", ans);
}
int main() {
  scanf("%d", &T);
  while (T--)
    solve();
  return 0;
}