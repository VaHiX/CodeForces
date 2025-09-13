/*
 * Problem URL : https://codeforces.com/problemset/problem/2091/F
 * Submit Date : 2025-08-22
 */

#include <cmath>
#include <iostream>
#include <stdio.h>
using namespace std;
#define endl '\n'
int pre[2001];
int add[2001];
char s[2003];
const int mod = 998244353;
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  int d = sqrt(k * k - 1);
  for (int j = 1; j <= m; j++)
    pre[j] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++)
      cin >> s[j];
    if (i > 1)
      for (int j = 1; j <= m; j++)
        if ((s[j]) == 'X')
          add[j] = pre[min(m, j + d)] - pre[max(0, j - d - 1)] + mod,
          add[j] %= mod;
        else
          add[j] = 0;
    if (i > 1)
      for (int j = 1; j <= m; j++)
        pre[j] = 0;
    // update the prefix array
    for (int j = 1; j <= m; j++)
      pre[j] = pre[j - 1] + ((i == 1) ? (s[j] == 'X') : add[j]), pre[j] %= mod;
    for (int j = 1; j <= m; j++)
      if (s[j] == 'X')
        add[j] = pre[min(m, j + k)] - pre[max(0, j - k - 1)] + mod,
        add[j] %= mod;
      else
        add[j] = 0;
    // update the prefix array
    for (int j = 1; j <= m; j++)
      pre[j] = pre[j - 1] + add[j], pre[j] %= mod;
  }
  cout << pre[m] << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}