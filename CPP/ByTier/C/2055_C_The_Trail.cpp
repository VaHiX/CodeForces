/*
 * Problem URL : https://codeforces.com/problemset/problem/2055/C
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e3 + 5;
int T, n, m, x, y;
string s;
ll a[maxn][maxn];
ll b[maxn], c[maxn];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    cin >> n >> m >> s;
    x = y = 1;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++) {
        cin >> a[i][j];
        b[i] += a[i][j];
        c[j] += a[i][j];
      }
    for (int i = 0; i < n + m - 2; i++)
      if (s[i] == 'D') {
        a[x][y] = -b[x];
        c[y] += a[x][y];
        x++;
      } else {
        a[x][y] = -c[y];
        b[x] += a[x][y];
        y++;
      }
    a[n][m] = -b[n];
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++)
        cout << a[i][j] << ' ';
      cout << '\n';
    }
    for (int i = 1; i <= n; i++)
      b[i] = 0;
    for (int j = 1; j <= m; j++)
      c[j] = 0;
  }
  return 0;
}