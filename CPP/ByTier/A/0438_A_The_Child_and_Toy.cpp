/*
 * Problem URL : https://codeforces.com/contest/438/problem/A
 * Submit Date : 2025-09-06
 */

#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int a[100005];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  int ans = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    ans += min(a[x], a[y]);
  }
  cout << ans;
  return 0;
}