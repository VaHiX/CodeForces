/*
 * Problem URL : https://codeforces.com/problemset/problem/2106/G2
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
#define int long long
#define FAST                                                                   \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
int n;
vector<int> v[1010];
bool del[1010];
int sz[1010];
int ppp[1010];
int cnt, rt;
int final;

void dfs(int d, int fa) {
  sz[d] = 1;
  ++cnt;
  for (auto i : v[d]) {
    if (!del[i] && i != fa) {
      dfs(i, d);
      sz[d] += sz[i];
    }
  }
  return;
}
void dfs2(int d, int fa) { //
  int mx = cnt - sz[d];
  for (auto i : v[d]) {
    if (!del[i] && i != fa) {
      dfs2(i, d);
      mx = max(mx, sz[i]);
    }
  }
  if (mx <= cnt / 2)
    rt = d;
  return;
}
void turnoff(int d, int fa) {
  del[d] = 1;
  for (auto i : v[d]) {
    if (i != fa && !del[i]) {
      turnoff(i, d);
    }
  }
}
int findleaf(int d, int fa) {
  for (auto i : v[d]) {
    if (i != fa && !del[i])
      return findleaf(i, d);
  }
  return d;
}

void play() {
  for (int i = 1; i <= n; i++) {
    if (!del[i]) {
      cnt = 0;
      dfs(i, 0);
      dfs2(i, 0);
      break;
    }
  }
  // 在 rt 的每个子树里面各找一个叶子
  vector<pair<int, int>> lf;
  for (auto i : v[rt]) {
    if (!del[i]) {
      lf.push_back({i, findleaf(i, rt)});
    }
  }
  if (lf.empty()) {
    final = rt;
    return;
  }
  while (1) {
    int t = lf.size();
    int Q = (t - 1) / 2;
    cout << "? " << 1 << " " << Q + 1 << " ";
    for (int i = 0; i <= Q; i++) {
      cout << lf[i].second << " ";
    }
    cout << "\n";
    int A1;
    cin >> A1;

    cout << "? " << 2 << " " << rt << "\n";

    cout << "? " << 1 << " " << Q + 1 << " ";
    for (int i = 0; i <= Q; i++) {
      cout << lf[i].second << " ";
    }
    cout << "\n";
    int A2;
    cin >> A2;

    if (abs(A1 - A2) == (Q + 1) * 2) {
      // 这个集合里面没有
      vector<pair<int, int>> qwq;
      for (int i = 0; i <= Q; i++)
        turnoff(lf[i].first, rt);
      for (int i = Q + 1; i < t; i++)
        qwq.push_back(lf[i]);
      lf = qwq;
      if (lf.empty()) {
        final = rt;
        return;
      }
    } else {
      // 集合里面有
      //			cout << "is\n";
      vector<pair<int, int>> qwq;
      for (int i = 0; i <= Q; i++)
        qwq.push_back(lf[i]);
      for (int i = Q + 1; i < t; i++)
        turnoff(lf[i].first, rt);
      lf = qwq;
      if (qwq.size() == 1) {
        del[rt] = 1;
        return;
      }
    }
  }
}
int SSS[1010];
void getans(int d, int fa) {
  cout << "? " << 1 << " " << 1 << " " << d << "\n";
  cin >> SSS[d];
  ppp[d] = SSS[d] - SSS[fa];
  for (auto i : v[d]) {
    if (i != fa)
      getans(i, d);
  }
}

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    v[i].clear();
    del[i] = 0;
  }
  for (int i = 1; i <= n - 1; i++) {
    int x, y;
    cin >> x >> y;
    v[x].push_back(y);
    v[y].push_back(x);
  }
  // 现在以 root 为根，然后 ori
  // 表示初始答案，取反根之后可以判断某个集合里面是否存在根 淀粉质，是对的
  final = 0;
  while (final == 0)
    play();
  getans(final, 0);
  cout << "! ";
  for (int i = 1; i <= n; i++)
    cout << ppp[i] << " ";
  cout << "\n";
  return;
}

signed main() {
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}