/*
 * Problem URL : https://codeforces.com/contest/2040/problem/D
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>
#define vector basic_string
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N = 2e5 + 5;
int _, n, a[N], x, y, tot;
vector<int> ve[N];
void dfs(int u, int fa) {
  a[u] = ++tot;
  int fl = 0;
  for (int v : ve[u])
    if (v != fa) {
      if (fl)
        while (((tot + 1 - a[u]) & 1) || (tot + 1 - a[u]) == 2)
          tot++;
      dfs(v, u);
      fl = 1;
    }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> _;
  while (_--) {
    cin >> n;
    for (int i = 1; i < n; i++)
      cin >> x >> y, ve[x].pb(y), ve[y].pb(x);
    tot = 0;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
      cout << a[i] << " \n"[i == n], ve[i].clear();
  }
}