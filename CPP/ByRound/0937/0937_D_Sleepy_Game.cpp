/*
 * Problem URL : https://codeforces.com/contest/937/problem/D
 * Submit Date : 2025-09-02
 */

#include <bits/stdc++.h>
using namespace std;
bool win, draw;
#define pb push_back
vector<int> v[100005], ans;
int vis[100005];
int view[100005][2];
bool iscycle(int n) {
  vis[n] = 1;
  for (int i = 0; i < v[n].size(); i++) {
    if (vis[v[n][i]] == 1)
      return true;
    else if (!vis[v[n][i]] && iscycle(v[n][i]))
      return true;
  }
  vis[n] = 2;
  return false;
}
bool run(int x, bool odd) {
  view[x][odd]++;
  bool ok = 1;
  if (v[x].size() == 0 && odd) {
    return 1;
  }
  for (int i = 0; i < v[x].size(); i++) {
    if (!view[v[x][i]][!odd] && run(v[x][i], !odd)) {
      ans.pb(v[x][i]);
      return 1;
    }
  }
  return 0;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  win = draw = false;
  int x, n, m, y;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    while (x--) {
      cin >> y;
      v[i].pb(y);
    }
  }
  cin >> x;
  if (run(x, 0)) {
    cout << "Win\n";
    ans.pb(x);
    reverse(ans.begin(), ans.end());
    for (int i : ans)
      cout << i << " ";
  }

  else if (iscycle(x))
    cout << "Draw";
  else
    cout << "Lose";
}
