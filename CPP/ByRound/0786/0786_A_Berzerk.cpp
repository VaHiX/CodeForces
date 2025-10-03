/*
 * Problem URL : https://codeforces.com/contest/786/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
const int N = 7010;

int n, k[2], a[2][N];
int win[2][N], vis[2][N], cnt[2][N];

void dfs(int per, int xb) {
  if (vis[per][xb])
    return;
  vis[per][xb] = 1;

  int u = per ^ 1;

  rep(i, 1, k[u]) {
    int pre = (xb - a[u][i]);
    if (pre < 1)
      pre += n;
    if (pre == 1)
      continue;
    if (win[per][xb] == 0) {
      win[u][pre] = 1;
      dfs(u, pre);
    } else if (++cnt[u][pre] == k[u]) {
      win[u][pre] = 0;
      dfs(u, pre);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  cin >> n;
  cin >> k[0];
  rep(i, 1, k[0]) cin >> a[0][i];
  cin >> k[1];
  rep(i, 1, k[1]) cin >> a[1][i];
  /*
          1 win
          2 lose
          3 loop
  */

  dfs(0, 1);
  dfs(1, 1);

  string s[4];
  s[1] = "Win", s[2] = "Lose", s[3] = "Loop";
  rep(i, 0, 1) {
    rep(j, 2, n) cout << (vis[i][j] ? win[i][j] ? s[1] : s[2] : s[3]) << " ";
    cout << "\n";
  }
}
