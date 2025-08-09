/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mp make_pair

int n, m, s, t, a, b, c, cap[914][914], INF = 1e8;

int bfs(vector<int> &par, int s, int t) {
  fill(par.begin(), par.end(), -1);
  par[s] = -2;
  queue<pair<int, int>> q;
  q.push(mp(s, 1e18));
  while (!q.empty()) {
    int f = q.front().first, c = q.front().second;
    q.pop();
    for (int i = 1; i <= max(n, t); i++)
      if (par[i] == -1 && cap[f][i]) {
        par[i] = f;
        int nc = min(c, cap[f][i]);
        if (i == t)
          return nc;
        q.push(mp(i, nc));
      }
  }
  return 0;
}

int max_flow(int s, int t) {
  int res = 0, nf;
  vector<int> par(max(n, t) + 100);
  while (nf = bfs(par, s, t)) {
    res += nf;
    int cnt = t;
    while (cnt != s) {
      int pr = par[cnt];
      cap[pr][cnt] -= nf;
      cap[cnt][pr] += nf;
      cnt = pr;
    }
  }
  return res;
}

signed main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> m;
    for (int j = 1; j <= m; j++)
      cin >> a, cap[i][a + n] += INF;
  }
  for (int i = 1; i <= n; i++)
    cin >> a, cap[0][i] += INF - a, c += a;
  for (int i = n + 1; i <= n * 2; i++)
    cap[i][n * 2 + 1] += INF;
  cout << c + max_flow(0, n * 2 + 1) - n * INF << endl;
  return 0;
}