/*
 * Problem URL : https://codeforces.com/problemset/problem/194/D
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
typedef pair<int, int> PII;
typedef long long ll;

const int N = 35;
const ll inf = 1e18;

int n, m, r;
int a[N][N], b[N], k[N], p[N];
ll ans = -inf;

void dfs(int u, bool xr) {
  if (u == m) {
    ll res = 0;
    for (int i = 0; i < n; i++)
      res += a[u][i] * k[i];
    ans = max(ans, res);
    return;
  }
  if (xr) {
    if (m - u & 1)
      for (int i = 0; i < n; i++)
        a[u][i] ^= b[i];
    ll res = 0;
    for (int i = 0; i < n; i++)
      res += a[u][i] * k[i];
    ans = max(ans, res);
    if (m - u & 1)
      for (int i = 0; i < n; i++)
        a[u][i] ^= b[i];
  } else {
    ll res = 0;
    for (int i = 0; i < n; i++)
      a[u + 1][i] = a[u][i] ^ b[i];
    dfs(u + 1, true);
  }
  for (int i = 0; i < n; i++)
    a[u + 1][i] = a[u][p[i] - 1] + r;
  dfs(u + 1, false);
}

void solve() {
  cin >> n >> m >> r;
  for (int i = 0; i < n; i++)
    cin >> a[0][i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  for (int i = 0; i < n; i++)
    cin >> k[i];
  for (int i = 0; i < n; i++)
    cin >> p[i];
  dfs(0, false);
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  solve();
  return 0;
}