/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 505;
const int INF = 1e9 + 5;

int n, m;
int x, y, z;
int dp[N][N];
int q;
int k;
int a[N];

void solve() {
  cin >> n >> m;
  vector<vector<int>> f(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++)
    f[i][i] = 0;
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> z;
    x--, y--;
    f[x][y] = min(f[x][y], z);
  }
  vector<vector<int>> g = f;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
      }
    }
  }
  cin >> q;
  while (q--) {
    cin >> k;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    string ans(n, '0');
    for (int i = 0; i < n; i++) {
      int z = a[i];
      for (int j = 0; j < n; j++) {
        z = min(z, f[i][j] + a[j]);
      }
      for (int j = 0; j < n; j++) {
        if (g[i][j] + a[j] - k < min(z, f[i][j] + a[j] - k)) {
          ans[i] = '1';
          break;
        }
      }
    }
    cout << ans << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  int yt = 1;
  //	cin >> yt;
  while (yt--) {
    solve();
  }

  return 0;
}
