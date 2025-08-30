/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int N = 1e5 + 10;
int n, m, ans;
int type[N], tg[2];
vector<int> e[N];

int ind[N];
queue<int> q;
bool vis[N];
vector<int> ord;
void work(bool tp) {
  for (int i = 1; i <= n; ++i)
    if (type[i] == tp && !vis[i] && !ind[i]) {
      vis[i] = 1;
      q.push(i);
    }
  while (!q.empty()) {
    int u = q.front();
    ord.push_back(u);
    q.pop();
    for (int v : e[u]) {
      --ind[v];
      if (type[v] == tp && !ind[v]) {
        vis[v] = 1;
        q.push(v);
      }
    }
  }
  return;
}
void add(int x) {
  if (ind[x]) {
    cout << -1;
    exit(0);
  }
  vis[x] = 1;
  ord.push_back(x);
  for (int v : e[x])
    --ind[v];
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s, t;
    bool op, v;
    cin >> s >> t;
    op = (s == "set");
    v = (t == "true");
    if (v) {
      if (tg[op]) {
        cout << -1;
        return 0;
      }
      tg[op] = i;
      type[i] = 2 + op;
    } else
      type[i] = op;
  }
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    cin >> x >> y;
    e[x].push_back(y);
    ++ind[y];
  }
  if (tg[0] && !tg[1]) {
    cout << -1;
    return 0;
  }
  work(0);
  if (tg[1]) {
    add(tg[1]);
    work(1);
    if (tg[0]) {
      add(tg[0]);
      work(0);
    }
  }
  if (ord.size() < n) {
    cout << -1;
    return 0;
  }
  for (int t : ord)
    cout << t << ' ';
  return 0;
}