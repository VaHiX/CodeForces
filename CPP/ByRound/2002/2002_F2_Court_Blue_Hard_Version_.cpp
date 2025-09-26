/*
 * Problem URL : https://codeforces.com/contest/2002/problem/F2
 * Submit Date : 2025-09-14
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, m, l, f;
int ans;
bool notp[20000010];
vector<int> pr;
map<pair<int, int>, int> vis;

void ss(int n) {
  notp[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!notp[i])
      pr.push_back(i);
    for (int j = 0; j < pr.size() && pr[j] * i <= n; j++) {
      notp[pr[j] * i] = 1;
      if (i % pr[j] == 0)
        break;
    }
  }
}

int dfs(int x, int y) {
  if (x < y)
    swap(x, y);
  if (__gcd(x, y) > 1)
    return 0;
  if (!notp[x])
    return 1;
  if (vis.count({x, y}))
    return vis[{x, y}];
  if (x != 1 && dfs(x - 1, y))
    return vis[{x, y}] = 1;
  if (y != 1 && dfs(x, y - 1))
    return vis[{x, y}] = 1;
  return vis[{x, y}] = 0;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ss(20000000);
  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> l >> f;
    ans = max(l * n + f, l + m * f);
    for (int i = n; i >= 2; i--) {
      if (i * l + m * f <= ans)
        break;
      for (int j = m; j >= 2; j--) {
        if (i * l + j * f <= ans)
          break;
        if (dfs(i, j))
          ans = i * l + j * f;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
/*
1
6 6 2 2
*/