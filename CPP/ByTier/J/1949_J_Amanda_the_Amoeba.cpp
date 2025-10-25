/*
 * Problem URL : https://codeforces.com/contest/1949/problem/J
 * Submit Date : 2025-09-07
 */

#include <bits/stdc++.h>
using namespace std;
#define rd(i, n) for (int i = 0; i < n; i++)
#define rp(i, n) for (int i = 1; i <= n; i++)
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = b; i >= a; i--)
#define st string
#define vt vector
#define pb push_back
// #define int long long
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m, v[55][55], vis[55][55], sx, sy, tx, ty, d1[55][55], d2[55][55],
    cur[55][55];
int stp[55][55], ccs, oqp[55][55];
int ide[55][55];
string s[55], t[55];
vt<pii> vv[55][55];
vt<pii> del;
vt<pii> add;
int cnt = 0;
set<pair<int, pii>> se, sp;
inline void dfs1(int x, int y) {
  vis[x][y] = 1;
  //	cout<<x<<" + "<<y<<endl;
  rd(k, 4) {
    int nx = x + dx[k], ny = y + dy[k];
    if (s[nx][ny] == '*') {
      if (!vis[nx][ny]) {
        dfs1(nx, ny);
      }
    }
  }
  stp[x][y] = ++cnt;
  se.insert({cnt, {x, y}});
}
vt<pair<pii, pii>> ans;
inline void dfs2(int x, int y) {
  vis[x][y] = 1;
  ide[x][y] = ++ccs;
  sp.insert({ccs, {x, y}});
  rd(k, 4) {
    int nx = x + dx[k], ny = y + dy[k];
    if (t[nx][ny] == '*') {
      if (!vis[nx][ny]) {
        dfs2(nx, ny);
      }
    }
  }
}
vt<pii> adds;
inline void bfs3() {
  queue<pii> q;
  q.push({tx, ty});
  vis[tx][ty] = 1;
  while (q.size()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    rd(k, 4) {
      int nx = x + dx[k], ny = y + dy[k];
      if (!v[nx][ny] && !vis[nx][ny]) {
        vis[nx][ny] = vis[x][y] + 1;
        q.push({nx, ny});
      }
    }
  }
  if (!vis[sx][sy]) {
    cout << "NO\n";
    exit(0);
  }
  cout << "YES\n";
  int x = sx, y = sy;
  while (x != tx || y != ty) {
    rd(k, 4) {
      int nx = x + dx[k], ny = y + dy[k];
      if (!v[nx][ny] && vis[nx][ny] == vis[x][y] - 1) {
        if (!cur[nx][ny]) {
          stp[nx][ny] = ++cnt;
          se.insert({stp[nx][ny], {nx, ny}});
          auto k = se.begin();
          ans.pb({{k->second.first, k->second.second}, {nx, ny}});
          se.erase(k);
          x = nx, y = ny, cur[x][y] = 1,
          cur[k->second.first][k->second.second] = 0;
        } else {
          se.erase({stp[nx][ny], {nx, ny}});
          stp[nx][ny] = ++cnt;
          se.insert({stp[nx][ny], {nx, ny}});
          x = nx, y = ny;
        }
        break;
      }
    }
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  rp(i, n) {
    cin >> s[i];
    s[i] = '$' + s[i];
  }
  rp(i, n) {
    cin >> t[i];
    t[i] = '$' + t[i];
  }
  rep(i, 0, n + 1) rep(j, 0, m + 1) v[i][j] = 1;
  rp(i, n) rp(j, m) v[i][j] = 0;
  rp(i, n) rp(j, m) if (s[i][j] == 'X') v[i][j] = 1;
  rp(i, n) rp(j, m) if (s[i][j] == '*') {
    sx = i, sy = j;
    dfs1(i, j);
    i = n + 1, j = m + 1;
  }
  rp(i, n) rp(j, m) vis[i][j] = 0;
  rp(i, n) rp(j, m) if (t[i][j] == '*') {
    tx = i, ty = j;
    dfs2(i, j);
    i = n + 1, j = m + 1;
  }
  rp(i, n) rp(j, m) vis[i][j] = 0;
  rp(i, n) rp(j, m) if (s[i][j] == '*') cur[i][j] = 1;
  bfs3();
  while (sp.size()) {
    auto k = sp.begin();
    int x = k->second.first, y = k->second.second;
    //		cout<<x<<" "<<y<<endl;
    if (!cur[x][y]) {
      auto kk = se.begin();
      int xx = kk->second.first, yy = kk->second.second;
      se.erase({stp[xx][yy], {xx, yy}});
      if (oqp[xx][yy])
        continue;
      ans.pb({{xx, yy}, {x, y}});
      se.erase({stp[x][y], {x, y}});
      cur[x][y] = 1, cur[xx][yy] = 0;
    } else {
      se.erase({stp[x][y], {x, y}});
    }
    oqp[x][y] = 1;
    sp.erase(k);
  }
  if (ans.size() > 10000)
    exit(1);
  cout << ans.size() << '\n';
  for (auto i : ans)
    cout << i.first.first << " " << i.first.second << " " << i.second.first
         << " " << i.second.second << '\n';

  return 0;
}
// Rain Rain Rain