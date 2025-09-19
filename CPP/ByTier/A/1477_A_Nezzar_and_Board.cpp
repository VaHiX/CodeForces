/*
 * Problem URL : https://codeforces.com/contest/1477/problem/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
int n, m, a[N];
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  int g = 0;
  for (int i = 2; i <= n; i++)
    g = __gcd(g, a[i] - a[1]);
  cout << ((m - a[1]) % g == 0 ? "YES\n" : "NO\n");
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int Case;
  cin >> Case;
  while (Case--)
    solve();
}