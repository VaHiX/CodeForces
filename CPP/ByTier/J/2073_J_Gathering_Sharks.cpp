/*
 * Problem URL : https://codeforces.com/contest/2073/problem/J
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n, a[N], p[N], f[N][N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> a[i], p[a[i]] = i;
  for (int l = 1; l < n; l++) {
    for (int j = 1; j + l <= n; j++) {
      int k = j + l;
      f[j][k] = 1e6;
      for (int i = j + 1; i <= k; i++) {
        f[j][k] = min(f[j][k], f[j][i - 1] + f[i][k] + abs(p[i] - p[j]));
      }
    }
  }
  cout << f[1][n] << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(), cout.tie();
  solve();
  return 0;
}